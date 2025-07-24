/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
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
#else
#define bug(x...) void(0)
#endif

inline int mod(int a, int m) {
    a %= m;
    return a < 0 ? a + m : a;
}
inline ll modll(ll a, ll m) {
    a %= m;
    return a < 0 ? a + m : a;
}

const int MOD = 998244353;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MAXN = 1e6 + 5;

vector<int> a[MAXN];
vector<pair<int,int> > b[MAXN];
bool used[MAXN];
int g1 = 0, g2 = 0;
pair<int,int> pr[MAXN];
int corn[MAXN];

pair<int,int> operator+(pair<int,int> a, pair<int,int> b) {
    return make_pair(mod(a.first + b.first, g1), mod(a.second + b.second, g2));
}
pair<int,int> operator-(pair<int,int> a, pair<int,int> b) {
    return make_pair(mod(a.first - b.first, g1), mod(a.second - b.second, g2));
}

ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void dfs(int x) {
    used[x] = true;
    rep(i, sz(a[x])) {
        int v = a[x][i];
        auto we = b[x][i];
        if (!used[v]) {
            corn[v] = corn[x] + 1;
            pr[v] = we + pr[x];
            dfs(v);
        }
    }
}

int solve(int x, int y, int px, int py) {
    x = mod(x, px);
    y = mod(y, py);
    int ans = INF;
    for (int realx : {x, x - px}) {
        for (int realy : {y, y - py}) {
            int ans1 = max({abs(realx), abs(realy), abs(realx - realy)});
            ans = min(ans, ans1);
        }
    }
    return ans;
}

ll u, v, w;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, X;
        cin >> n >> m >> X;

        rep(i, n) {
            a[i].clear();
            b[i].clear();
            used[i] = false;
            corn[i] = 0;
        }
        pr[0] = {0, 0};
        g1 = 0;
        g2 = 0;

        vector<pair<pair<int,int>, pair<int,int> > > ed;

        rep(i, m) {
            int x, y, ww;
            cin >> x >> y >> ww;
            --x;
            --y;
            a[x].pb(y);
            a[y].pb(x);
            char c;
            cin >> c;
            if (c == 'r') {
                g1 = gcd(g1, 2LL * ww);
                b[x].pb({ww, 0});
                b[y].pb({ww, 0});
            } else if (c == 'g') {
                g2 = gcd(g2, 2LL * ww);
                b[x].pb({0, ww});
                b[y].pb({0, ww});
            } else {
                b[x].pb({-ww, -ww});
                b[y].pb({-ww, -ww});
            }
            ed.pb({{x, y}, b[x].back()});
        }

        u = g1;
        v = 0;
        w = g2;
        dfs(0);
        pair<int,int> que = pr[n-1];

        for (auto [h1, w1] : ed) {
            auto [x, y] = h1;
            if (corn[x] > corn[y]) swap(x, y);
            auto w2 = pr[y] - pr[x] + w1;
            ll d = w2.first;
            ll e = w2.second;
            if (d < 0) {
                d = -d;
                e = -e;
            }
            d = modll(d, g1);
            e = modll(e, g2);
            while (true) {
                if (!u) {
                    swap(u, d);
                    swap(v, e);
                    break;
                }
                if (!d) {
                    break;
                }
                if (abs(u) >= abs(d)) {
                    ll c = u / d;
                    u -= c * d;
                    v -= c * e;
                    v = modll(v, g2);
                } else {
                    ll c = d / u;
                    d -= c * u;
                    e -= c * v;
                    e = modll(e, g2);
                }
            }
            w = gcd(abs(w), abs(e));
            w = abs(w);
        }

        ll x1 = que.first;
        ll y1 = que.second;
        g1 = gcd(g1, abs(u) * (ll)g2);
        int res = INF;

        rep(c1, g2) {
            ll x2 = x1 - (ll)c1 * u;
            ll y2 = y1 - (ll)c1 * v;
            x2 = modll(x2, g1);
            y2 = modll(y2, g2);
            ll w1 = gcd(abs(w), (ll)g2);
            res = min(res, solve(x2, y2, g1, w1));
        }
        cout << res << '\n';
    }
    return 0;
}