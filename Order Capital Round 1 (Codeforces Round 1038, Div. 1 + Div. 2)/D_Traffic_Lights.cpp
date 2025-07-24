/*
Derrick (Tomato_Cultivator)
*/
 
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
#define fi first
#define se second
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
 
void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}
 
const int MOD = 998244353;
const int INF = 1e18;
const int MAX = 1e6 + 7;
 
ll modpow(ll a, ll b, ll m = MOD) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
 
ll modinv(ll a, ll m = MOD) {
    return modpow(a, m - 2, m);
}
 
template<class T> bool chmin(T& a, T b) { return (b < a ? a = b, true : false); }
template<class T> bool chmax(T& a, T b) { return (b > a ? a = b, true : false); }
 
int n, m;
vector<int> adj[MAX];
 
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) adj[i].clear();
 
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
 
    vector<int> cur(n + 1, INF), nxt(n + 1, INF);
    cur[1] = 0;
 
    int ans_t = -1, ans_w = -1;
 
    for (int t = 0; t <= 2 * n; ++t) {
        fill(all(nxt), INF);
        for (int u = 1; u <= n; ++u) {
            int w = cur[u];
            if (w == INF) continue;
 
            int d = adj[u].size();
            if (d > 0) {
                int idx = t % d;
                int v = adj[u][idx];
                chmin(nxt[v], w);
            }
            chmin(nxt[u], w + 1);
        }
        if (nxt[n] < INF) {
            ans_t = t + 1;
            ans_w = nxt[n];
            break;
        }
        swap(cur, nxt);
    }
 
    cout << ans_t << " " << ans_w << '\n';
}
 
int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
