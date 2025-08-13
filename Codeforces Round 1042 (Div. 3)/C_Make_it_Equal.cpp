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
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

static uint64_t RD = [](){
    uint64_t x = chrono::steady_clock::now().time_since_epoch().count();
    x ^= (uint64_t)(uintptr_t(new int));
    return x;
}();

void solve() {
    int n; ll k;
    input(n, k);
    vector<ll> A(n), B(n);
    rep(i,n) input(A[i]);
    rep(i,n) input(B[i]);
    unordered_map<uint64_t, int> cnt;
    cnt.reserve(n * 2 + 7);
    auto norm = [&](ll x)->ll{
        ll r = x % k;
        if (r < 0) r += k;
        return r;
    };
    rep(i,n){
        ll r = norm(A[i]);
        ll g = std::min(r, k - r);
        uint64_t key = ((uint64_t)g) ^ RD;
        ++cnt[key];
    }
    rep(i,n){
        ll r = norm(B[i]);
        ll g = std::min(r, k - r);
        uint64_t key = ((uint64_t)g) ^ RD;
        --cnt[key];
    }
    for (auto &p : cnt) {
        if (p.se != 0) {
            print("NO");
            return;
        }
    }
    print("YES");
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
