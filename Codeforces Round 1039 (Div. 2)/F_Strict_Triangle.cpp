/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)

const int MOD = 1e9+7;

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}

void solve() {
    int n, m, k;
    input(n, m, k);
    --k;
    vector<vector<array<int,3>>> adj(n);
    rep(i, m) {
        int u, v; ll l, r;
        input(u, v, l, r);
        --u; --v;
        adj[u].pb({v, (int)l, (int)r});
        adj[v].pb({u, (int)l, (int)r});
    }
    vector<ll> dk(n, -1);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0LL, k);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); pq.pop();
        if (dk[x] != -1) continue;
        dk[x] = d;
        for (auto &e : adj[x]) {
            int y = e[0], r = e[2];
            pq.emplace(d + r, y);
        }
    }
    vector<ll> dp(n);
    vector<char> vis(n, 0);
    pq.emplace(-dk[0], 0);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); pq.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        dp[x] = d;
        for (auto &e : adj[x]) {
            int y = e[0], l = e[1];
            ll nd = max(d + l, -dk[y]);
            if (nd < dk[y]) {
                pq.emplace(nd, y);
            }
        }
    }
    print(vis[n-1] ? "YES" : "NO");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    input(T);
    while (T--) solve();
    return 0;
}