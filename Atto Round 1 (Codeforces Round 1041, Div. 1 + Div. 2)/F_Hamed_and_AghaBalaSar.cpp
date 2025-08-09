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
const int MAXN = 400005;
const ll INF = 1e18;

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

ll fact[MAXN], invfact[MAXN];

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
}

ll c_bounded(int l, int s, int k) {
    if (l < 0 || s < 0) return 0;
    if (!l) return s == 0;
    int K = k + 1;
    ll res = 0;
    for (int j = 0, lim = s / K; j <= lim; ++j) {
        ll term = C(l, j) * C(s - j * K + l - 1, l - 1) % MOD;
        if (j & 1) res = (res - term + MOD) % MOD;
        else res = (res + term) % MOD;
    }
    return res;
}

pair<ll, ll> Fcalc(int l, int B, int k) {
    if (l < 0 || B < 0) return {0, 0};
    if (!l) return {1, 0};
    int K = k + 1;
    ll F1 = 0, F2 = 0;
    for (int j = 0, lim = B / K; j <= lim; ++j) {
        int Nj = B - j * K;
        ll choose_l_j = C(l, j);
        ll t1 = C(Nj + l, l);
        ll add1 = choose_l_j * t1 % MOD;
        ll t2 = (ll)l * C(Nj + l, l + 1) % MOD;
        ll t3 = (ll)j * K % MOD * t1 % MOD;
        ll add2 = choose_l_j * (t2 + t3) % MOD;
        if (j & 1) {
            F1 = (F1 - add1 + MOD) % MOD;
            F2 = (F2 - add2 + MOD) % MOD;
        } else {
            F1 = (F1 + add1) % MOD;
            F2 = (F2 + add2) % MOD;
        }
    }
    return {F1, F2};
}

void solve() {
    int n, m;
    input(n, m);
    int len_tot = n - 1;
    ll ans = 0;

    rep(k, m + 1) {
        int s = m - k;
        ll A1 = (c_bounded(len_tot, s, k) - c_bounded(len_tot - 1, s - k, k) + MOD) % MOD;

        int len1 = len_tot - 1;
        auto P1 = Fcalc(len1, s, k);
        auto P2 = Fcalc(len1, s - k, k);
        ll S1 = (P1.first - P2.first + MOD) % MOD;
        ll S2 = (P1.second - P2.second + MOD) % MOD;

        ll B1 = ((ll)s % MOD) * S1 % MOD;
        B1 = (B1 - S2 + MOD) % MOD;

        int len2 = len_tot - 2;
        auto P3 = Fcalc(len2, s - k, k);
        auto P4 = Fcalc(len2, s - 2 * k, k);
        ll S1b = (P3.first - P4.first + MOD) % MOD;
        ll S2b = (P3.second - P4.second + MOD) % MOD;

        ll B2 = ((ll)(s - k) % MOD) * S1b % MOD;
        B2 = (B2 - S2b + MOD) % MOD;

        ll part1 = ((ll)k % MOD) * (A1 + (ll)(len_tot - 1) * S1b % MOD) % MOD;
        ll part2 = (B1 + (ll)(len_tot - 1) * B2 % MOD) % MOD;

        ll term = (part1 - part2 + MOD) % MOD;
        ans = (ans + term) % MOD;
    }

    print(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i >= 1; --i) invfact[i - 1] = invfact[i] * i % MOD;

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
