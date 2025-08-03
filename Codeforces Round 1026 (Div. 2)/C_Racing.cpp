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

const int MOD = int(1e9) + 7;

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{";
    int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...)     bug_(32, x)
#else
#define bug(x...) void(0)
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
void print() { cout << '\n'; }

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve(){
    int n;
    input(n);
    vi d(n);
    rep(i,n) input(d[i]);
    vi l(n), r(n);
    rep(i,n) input(l[i], r[i]);

    int h = 0;
    vi last; 

    rep(i,n){
        if (d[i] == -1) {
            last.pb(i);
        } else {
            h += d[i];
        }

        while (h < l[i]) {
            if (last.empty()) {
                print(-1);
                return;
            }
            int idx = last.back(); last.pop_back();
            d[idx] = 1;
            h++;
        }

        while (h + (int)last.size() > r[i]) {
            if (last.empty()) {
                print(-1);
                return;
            }
            int idx = last.back(); last.pop_back();
            d[idx] = 0; 
        }
    }
    rep(i,n){
        int x = max(0, d[i]);
        cout << x << (i+1<n ? ' ' : '\n');
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
