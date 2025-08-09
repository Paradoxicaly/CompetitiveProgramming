/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

const int MXN = 200000 + 5;
const int LOG = 18;

int n, k;
ll w[MXN];
int color[MXN], cnt[MXN], col2[MXN];
int par[LOG][MXN], stt[MXN], h[MXN], timer;
vector<int> g[MXN], cols[MXN];
bool mark[MXN], cutie[MXN];

void dfs_lca(int v) {
    stt[v] = timer++;
    for (int i = 1; i < LOG; i++)
        par[i][v] = par[i-1][ par[i-1][v] ];
    for (int u : g[v]) if (u != par[0][v]) {
        h[u] = h[v] + 1;
        par[0][u] = v;
        dfs_lca(u);
    }
}

int jump(int v, int d) {
    rep(i,LOG) if (d>>i & 1) v = par[i][v];
    return v;
}

int LCA(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    u = jump(u, h[u] - h[v]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}

void dfs_color(int v, int cc) {
    if (color[v]) cc = color[v];
    else color[v] = cc;
    for (int u : g[v]) if (u != par[0][v]) {
        dfs_color(u, cc);
    }
}

void solve() {
    input(n, k);
    timer = 0;
    rng(i,1,n+1) {
        cnt[i] = col2[i] = 0;
        mark[i] = cutie[i] = false;
        cols[i].clear();
        g[i].clear();
        color[i] = h[i] = 0;
    }
    rng(i,1,n+1) input(w[i]);
    rng(i,1,n+1) {
        input(color[i]);
        if (color[i]) cols[color[i]].pb(i);
    }
    rep(_, n-1) {
        int u, v;
        input(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    bool any = false;
    rng(i,1,n+1) if (color[i]) { any = true; break; }
    if (!any) {
        print(0);
        rng(i,1,n+1) cout << 1 << " ";
        print();
        return;
    }

    par[0][1] = 0;
    h[1] = 0;
    dfs_lca(1);

    rng(ci,1,k+1) {
        auto &C = cols[ci];
        sort(all(C), [&](int a,int b){ return stt[a] < stt[b]; });
        vector<int> temp;
        rep(j, sz(C)-1) {
            int u = C[j], v = C[j+1];
            int lca = LCA(u, v);
            if (!mark[lca]) {
                if (color[lca]) {
                    if (color[lca] != ci) cutie[lca] = true;
                } else {
                    mark[lca] = true;
                    cnt[lca]++;
                    col2[lca] = ci;
                    temp.pb(lca);
                }
            }
        }
        for (int x : temp) mark[x] = false;
    }

    ll ans = 0;
    rng(i,1,n+1) {
        if (cutie[i] || cnt[i] > 1) ans += w[i];
        if (!color[i] && cnt[i] == 1) color[i] = col2[i];
    }
    print(ans);

    rng(i,1,n+1) if (color[i]) {
        dfs_color(1, color[i]);
        break;
    }

    rng(i,1,n+1) cout << color[i] << " ";
    print();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
