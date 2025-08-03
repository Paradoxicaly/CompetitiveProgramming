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
template <typename T>
ostream& operator<<(ostream &o, vector<T> v) {
    o << "{";
    int f = 0;
    for (auto &&x : v)
        o << (f++ ? " " : "") << x;
    return o << "}";
}
void bug__(int c, auto... a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m\n";
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...)    bug_(32, x)
#else
#define bug(x...)    void(0)
#endif

template<class... T>
constexpr auto min(T... a){ return std::min({a...}); }
template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    ((cout << ' ' << b), ...);
    cout << '\n';
}

ll gcd(ll a, ll b){ return b ? gcd(b, a % b) : a; }
ll power(ll a, ll b, ll m = MOD){
    ll r = 1;
    while (b){
        if (b & 1) r = (r * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return r;
}

void solve(){
    int n, m;
    input(n, m);
    vector<ll> b(n);
    rep(i,n) input(b[i]);

    vector<vector<pair<int,int>>> graph(n);
    rep(i,m){
        int u, v;
        ll w;
        input(u, v, w);
        --u; --v;
        graph[u].pb({v, (int)w});
    }

    const int INF = int(1e9) + 11;
    auto check = [&](int maxW){
        vector<ll> best(n, 0);
        rep(i,n){
            if (i > 0 && best[i] == 0) continue;
            best[i] = min<ll>(maxW, best[i] + b[i]);
            for (auto &e : graph[i]){
                if (e.se <= best[i]){
                    best[e.fi] = max(best[e.fi], best[i]);
                }
            }
        }
        return best[n-1] > 0;
    };

    if (!check(INF)){
        print(-1);
        return;
    }

    int lo = 0, hi = INF;
    while (hi - lo > 1){
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    print(hi);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
