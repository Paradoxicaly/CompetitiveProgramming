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
 
const int MOD = 1e9 + 7;
 
template<class... T>
constexpr auto min(T... a){ return std::min({a...}); }
template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }
template<class... T>
void input(T&... a){ (cin >> ... >> a); }
template<class T, class... Ts>
void print(const T& a, const Ts&... b){ cout << a; (cout << ... << (cout << ' ', b)); cout << '\n'; }
void print() { cout << '\n'; }
 
struct KthDS {
    static const int SHIFT = 9;
    static const int SQ = 1 << SHIFT;
    int V, NB;
    vector<int> cnt, buck;
    void reset(int maxv){
        V = maxv;
        NB = (V + SQ - 1) / SQ;
        cnt.assign(NB * SQ, 0);
        buck.assign(NB, 0);
    }
    inline void add(int x, int d){
        cnt[x] += d;
        buck[x >> SHIFT] += d;
    }
    int kth(int k){
        for (int b = 0; b < NB; ++b){
            if (buck[b] < k) k -= buck[b];
            else{
                int L = b << SHIFT, R = min(V, (b + 1) << SHIFT);
                for (int x = L; x < R; ++x){
                    if (cnt[x] < k) k -= cnt[x];
                    else return x;
                }
            }
        }
        return V - 1;
    }
};
 
int upPowRange(int n){
    int b = 31 - __builtin_clz(n);
    return 1 << (b + 1);
}
 
void solve() {
    int n, m; input(n, m);
    vector<vector<int>> G(n + 2), H(n + 2);
    vector<int> deg(n + 2, 0), xo(n + 2, 0), on(n + 2, 0);
    rep(i,m){
        int u, v; input(u, v);
        if (u > v) swap(u, v);
        deg[u]++;
        G[u].pb(v);
        H[v].pb(u);
    }
    vector<int> ct(1, 1);
    long long cur = 0;
    for (int i = 1; i <= n; ++i){
        if (cur + deg[i] <= 512 && i + 1 - ct.back() <= 512) cur += deg[i];
        else{
            if (ct.back() < i) ct.pb(i);
            if (deg[i] >= 512){ ct.pb(i + 1); cur = 0; }
            else cur = deg[i];
        }
    }
    if (ct.back() != n + 1) ct.pb(n + 1);
 
    int q; input(q);
    vector<int> L(q), R(q), K(q), ans(q);
    vector<pair<int,int>> ord; ord.reserve(q);
    rep(i,q){
        input(L[i], R[i], K[i]);
        R[i]++;
        int idx = lower_bound(all(ct), L[i]) - ct.begin();
        ord.pb({idx, i});
    }
    sort(all(ord), [&](const pair<int,int>& a, const pair<int,int>& b){
        if (a.fi != b.fi) return a.fi < b.fi;
        return R[a.se] < R[b.se];
    });
 
    int MAXV = upPowRange(n);
    KthDS ds; ds.reset(MAXV);
 
    auto Xor = [&](int i, int x){
        if (on[i]) ds.add(xo[i], -1);
        xo[i] ^= x;
        if (on[i]) ds.add(xo[i], +1);
    };
    auto ToggleEdge = [&](int u, int v){
        Xor(u, v);
        Xor(v, u);
    };
    auto ToggleVertex = [&](int u){
        ds.add(xo[u], on[u] ? -1 : +1);
        on[u] ^= 1;
    };
    auto Do = [&](const vector<int>& ad, int l, int r, int u){
        for (int adj : ad) if (l <= adj && adj < r) ToggleEdge(adj, u);
    };
 
    int cl = 1, cr = 1;
    for (auto pr : ord){
        int id = pr.se;
        while (cr < R[id]){
            Do(H[cr], cl, cr, cr);
            ToggleVertex(cr);
            cr++;
        }
        while (cl > L[id]){
            Do(G[cl - 1], cl, cr, cl - 1);
            cl--;
            ToggleVertex(cl);
        }
        while (cr > R[id]){
            Do(H[cr - 1], cl, cr, cr - 1);
            ToggleVertex(cr - 1);
            cr--;
        }
        while (cl < L[id]){
            Do(G[cl], cl, cr, cl);
            ToggleVertex(cl);
            cl++;
        }
        ans[id] = ds.kth(K[id]);
    }
    rep(i,q) print(ans[i]);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}