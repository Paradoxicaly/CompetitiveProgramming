/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define fi first
#define se second

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define pb push_back

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MOD = 998244353;
ll modpow(ll a, ll b, ll m = MOD) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
ll modinv(ll a, ll m = MOD) {
    return modpow(a, m - 2, m);
}

const int MAX = 200005;
ll fact[MAX], ifact[MAX];
void init_factorials() {
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fact[i] = fact[i-1] * i % MOD;
        ifact[i] = modinv(fact[i]);
    }
}
ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

template<class T> bool chmin(T& a, T b) { return (b < a ? a = b, true : false); }
template<class T> bool chmax(T& a, T b) { return (b > a ? a = b, true : false); }

ll pw(ll a, ll e = MOD - 2) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    cincout();
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> v(m+2);
    ll A = 1, B = 1;
    rep(i, n) {
        int l, r;
        ll p, q;
        cin >> l >> r >> p >> q;
        ll d = q - p;
        A = A * d % MOD;
        B = B * q % MOD;
        ll ci = p * pw(d) % MOD;
        v[l].emplace_back(r, (int)ci);
    }
    ll X = A * pw(B) % MOD;
    vector<ll> dp(m+3);
    dp[m+1] = 1;
    for (int i = m; i >= 1; i--) {
        ll s = 0;
        for (auto &pr : v[i])
            s = (s + pr.second * dp[pr.first + 1]) % MOD;
        dp[i] = s;
    }
    ll ans = X * dp[1] % MOD;
    if (ans < 0) ans += MOD;
    cout << ans;
    return 0;
}