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

#ifdef Tomato
template<typename T>
ostream& operator<<(ostream &o, const vector<T>& v) {
    o << "{";
    int f = 0;
    for (auto&& x : v)
        o << (f++ ? " " : "") << x;
    return o << "}";
}
void bug__(int c, auto... a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m\n";
}
#define bug_(c,x...) bug__(c,__LINE__,"[" #x "]",x)
#define bug(x...)    bug_(32,x)
#else
#define bug(x...)    void(0)
#endif

template<class... T>
void input(T&... a) { (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    ((cout << ' ' << b), ...);
    cout << '\n';
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll power(ll a, ll b, ll m = MOD) {
    ll r = 1;
    while (b) {
        if (b & 1) r = (r * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return r;
}

void solve() {
    int n;
    input(n);
    vector<pair<int,int>> s(n);
    rep(i,n) input(s[i].fi, s[i].se);

    map<int,int> mpV, mpP;
    map<pair<int,int>,int> toI;
    vector<pair<int,int>> part;
    vector<set<int>> g;

    rep(i,n) {
        int v = s[i].fi, p = s[i].se;
        toI[{v,p}] = i+1;
        if (!mpP.count(p)) {
            mpP[p] = sz(g);
            g.pb(set<int>());
            part.pb({0,p});
        }
        if (!mpV.count(v)) {
            mpV[v] = sz(g);
            g.pb(set<int>());
            part.pb({v,0});
        }
        int uV = mpV[v], uP = mpP[p];
        g[uV].insert(uP);
        g[uP].insert(uV);
    }

    int odd = 0, st = 0;
    rep(i, sz(g)) {
        if (sz(g[i]) % 2) {
            odd++;
            st = i;
        }
    }
    if (odd != 0 && odd != 2) {
        print("NO");
        return;
    }
    if (odd == 0) {
        rep(i, sz(g)) {
            if (!g[i].empty()) { st = i; break; }
        }
    }

    vector<int> ans;
    ans.reserve(n+1);
    function<void(int)> dfs = [&](int u) {
        while (!g[u].empty()) {
            int v = *g[u].begin();
            g[u].erase(v);
            g[v].erase(u);
            dfs(v);
        }
        ans.pb(u);
    };
    dfs(st);

    if (sz(ans) != n + 1) {
        print("NO");
        return;
    }

    vector<int> out;
    out.reserve(n);
    rep(i,n) {
        auto p1 = part[ans[i]];
        auto p2 = part[ans[i+1]];
        int vv = p1.fi + p2.fi;
        int pp = p1.se + p2.se;
        auto it = toI.find({vv,pp});
        if (it == toI.end()) {
            out.clear();
            break;
        }
        out.pb(it->second);
    }

    if (out.empty()) {
        print("NO");
    } else {
        print("YES");
        rep(i,n) cout << out[i] << (i+1<n?' ':'\n');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
