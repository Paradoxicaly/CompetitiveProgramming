/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, int>;

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

const ll INF = 1LL << 60;
const int N = 1e5 + 5;
int n, m, s, l, e;
vector<pii> g[N];

vector<ll> dijkstra(int start) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void solve() {
    cin >> n >> m >> s >> l >> e;
    rep(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].pb({v, w});
        g[v].pb({u, w});
    }

    vector<ll> d_powder = dijkstra(s);
    vector<ll> d_enf_start = dijkstra(e);
    vector<ll> d_enf_to_lab = dijkstra(l);

    // Enforcers path: e -> s -> l
    ll t_enf = d_enf_start[s] + d_enf_to_lab[s];
    ll t_pow = d_powder[l];

    if (t_pow >= t_enf) {
        cout << -1 << '\n';
        return;
    }

    // Check for any collision on common nodes during traversal
    rep(v, n + 1) {
        if (d_powder[v] < d_enf_start[v]) continue;
        if (d_enf_start[v] + d_enf_to_lab[v] == t_enf) {
            if (d_powder[v] == d_enf_start[v]) {
                cout << -1 << '\n';
                return;
            }
        }
    }

    cout << t_pow << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}