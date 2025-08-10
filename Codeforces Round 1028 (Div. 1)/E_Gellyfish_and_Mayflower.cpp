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

const ll INF = 0xcfcfcfcfcfcfcfcf;
const int N = 205;

#ifdef Tomato
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
#else
#define bug(x...) void(0)
#endif

inline ll sqr(ll x) { return x * x; }

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void checkmax(ll &a, ll b) {
    if (b > a) a = b;
}

ll n, m, magic = 0;
ll w[N], c[N];
ll f[N][N * N];
ll g[N][N][N][2];
vector<vi> G(N);

void main_min() {
    memset(f, 0xcf, sizeof(f));
    for (ll x = 0; x <= magic; ++x) f[1][x] = 0;

    for (ll u = 1; u <= n; ++u) {
        for (ll x = 0; x + c[u] <= magic; ++x) 
            checkmax(f[u][x + c[u]], f[u][x] + w[u]);

        for (ll v : G[u]) {
            for (ll x = 0; x <= magic; ++x)
                checkmax(f[v][x], f[u][x]);
        }
    }
}

void solve_max(ll i) {
    ll a = c[i], b = w[i];
    for (ll x = 0; x < a; ++x)
        g[i][1][x][0] = 0;

    for (ll u = 1; u <= n; ++u) {
        if (u == i) {
            for (ll x = 0; x < a; ++x)
                checkmax(g[i][u][x][1], g[i][u][x][0]);
        }
        else if (w[u] * a > c[u] * b) {
            memset(g[i][u], 0xcf, sizeof(g[i][u]));
        }

        ll k = gcd(c[u], a);
        for (ll s = 0; s < k; ++s) {
            for (ll x = s, t = 0; t < 2 * (a / k); ++t, x = (x + c[u]) % a) {
                checkmax(g[i][u][(x + c[u]) % a][0], g[i][u][x][0] + w[u] - ((x + c[u]) / a) * b);
                checkmax(g[i][u][(x + c[u]) % a][1], g[i][u][x][1] + w[u] - ((x + c[u]) / a) * b);
            }
        }

        for (ll v : G[u]) {
            for (ll x = 0; x < a; ++x) {
                checkmax(g[i][v][x][0], g[i][u][x][0]);
                checkmax(g[i][v][x][1], g[i][u][x][1]);
            }
        }
    }
}

void main_max() {
    memset(g, 0xcf, sizeof(g));
    for (ll i = 1; i <= n; ++i)
        solve_max(i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    rep(i, n) {
        cin >> c[i + 1] >> w[i + 1];
        magic = max(magic, sqr(c[i + 1]));
    }

    rep(i, m) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
    }

    main_min();
    main_max();

    int q;
    cin >> q;
    while (q--) {
        ll p, r;
        cin >> p >> r;
        if (r <= magic) {
            cout << f[p][r] << '\n';
        } else {
            ll ans = INF;
            for (ll i = 1; i <= n; ++i) {
                ll a = c[i], b = w[i];
                checkmax(ans, g[i][p][r % a][1] + (r / a) * b);
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
