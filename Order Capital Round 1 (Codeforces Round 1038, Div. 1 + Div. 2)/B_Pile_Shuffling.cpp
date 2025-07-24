/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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

const int N = 1e6 + 7;
int n;
ll a[N], b[N], c[N], d[N];

void solve() {
    cin >> n;
    ll ans = 0;
    rep(i, n) cin >> a[i] >> b[i] >> c[i] >> d[i];

    rep(i, n) {
        ans += max(0LL, a[i] - c[i]);
        ans += max(0LL, b[i] - d[i]);
    }
    rep(i, n) {
        if (b[i] > d[i]) {
            ans += min(a[i], c[i]);
        }
    }
    cout << ans << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}