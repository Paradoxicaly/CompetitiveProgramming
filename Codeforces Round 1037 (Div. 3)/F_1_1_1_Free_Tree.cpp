/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())
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

const int mod = 998244353, N = 1000005;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x, --x;

    vector<vector<pii>> adj(n);
    vector<bool> small(n, false);
    ll totw = 0;

    rep(i, n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        totw += w;
    }

    rep(i, n) if (sz(adj[i]) <= 450) small[i] = true;

    vector<pii> queries(q);
    for (auto &[v, x] : queries) cin >> v >> x, --v, --x;

    vector<ll> ans(q);
    auto tmp = a;
    ll cur = 0;

    // small-small optimization
    rep(i, n) if (small[i]) {
        for (auto [j, w] : adj[i]) if (small[j] && i < j) {
            if (a[i] == a[j]) cur += w;
        }
    }

    rep(i, q) {
        auto [v, x] = queries[i];
        if (small[v]) {
            for (auto [u, w] : adj[v]) if (small[u]) {
                if (a[v] == a[u]) cur -= w;
                if (x == a[u]) cur += w;
            }
        }
        a[v] = x;
        bug(i, cur);
        ans[i] = cur;
    }

    a = tmp;

    rep(i, n) if (!small[i]) {
        vector<ll> tot(n), vis(n);
        for (auto [j, w] : adj[i]) if (small[j] || i < j) {
            tot[a[j]] += w;
            vis[j] = w;
        }
        rep(qid, q) {
            auto [v, x] = queries[qid];
            tot[a[v]] -= vis[v];
            a[v] = x;
            tot[a[v]] += vis[v];
            ans[qid] += tot[a[i]];
        }
        a = tmp;
    }

    rep(i, q) cout << totw - ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}