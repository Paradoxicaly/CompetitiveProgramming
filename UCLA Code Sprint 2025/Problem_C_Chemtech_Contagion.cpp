/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

#ifdef Doludu
template <typename T>
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif

const int N = 2e5 + 5, LG = 18;
int n, m, q;
vector<int> g[N];
vector<pii> vents;
int up[N][LG], depth[N];

void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i < LG; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    for (int u : g[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LG; ++i)
        if (diff >> i & 1)
            u = up[u][i];
    if (u == v) return u;
    for (int i = LG - 1; i >= 0; --i)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}

void mark_path(int u, int v, int anc, unordered_set<int> &visited) {
    while (u != anc) {
        visited.insert(u);
        u = up[u][0];
    }
    while (v != anc) {
        visited.insert(v);
        v = up[v][0];
    }
    visited.insert(anc);
}

void solve() {
    cin >> n >> m >> q;
    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 1);

    vents.clear();
    rep(i, m) {
        int u, v;
        cin >> u >> v;
        vents.pb({u, v});
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        unordered_set<int> contaminated;
        int anc = lca(u, v);
        mark_path(u, v, anc, contaminated);

        int res = 0;
        for (auto [a, b] : vents) {
            if ((contaminated.count(a) && !contaminated.count(b)) ||
                (!contaminated.count(a) && contaminated.count(b))) {
                res++;
            }
        }

        cout << res << '\n';
    }

    rep(i, n + 1) g[i].clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}