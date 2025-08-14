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

template<class... T>
constexpr auto min(T... a){
    return std::min({a...});
}

template<class... T>
constexpr auto max(T... a){
    return std::max({a...});
}

template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1 % mod;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    long long k;
    input(n, k);
    vector<long long> a(n);
    rep(i,n) cin >> a[i];
    sort(all(a));
    long long ans = 1;
    for (int i = 0; i < n && k > 0; ++i) {
        ans = (ans * (a[i] % MOD)) % MOD;
        --k;
        if (k == 0) break;
        long long t;
        if (a[i] >= 32) t = k;
        else {
            long long F = (1LL << (a[i] - 1)) - 1;
            if (F < 0) F = 0;
            t = min(k, F);
        }
        long long rem = t;
        for (int j = 0; (rem >> j) > 0; ++j) {
            long long cnt = (rem >> j) - (rem >> (j + 1));
            ans = (ans * power(j + 1, cnt)) % MOD;
        }
        k -= rem;
    }
    print(ans % MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}