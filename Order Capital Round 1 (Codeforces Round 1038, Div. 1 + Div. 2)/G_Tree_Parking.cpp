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
#define pb push_back
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define rrep(i,a,b) for (int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MOD = 998244353;
const int N = 4e5 + 5;

ll fac[N], ifac[N], inv[N];

ll modpow(ll a, ll b, ll m = MOD) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

int rd() {
    char c;
    int f = 1;
    while (!isdigit(c = getchar())) if (c == '-') f = -1;
    int x = c - '0';
    while (isdigit(c = getchar())) x = x * 10 + (c ^ 48);
    return x * f;
}

int main() {
    cincout();

    fac[0] = ifac[0] = inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;

    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % MOD;
        ifac[i] = ifac[i - 1] * inv[i] % MOD;
    }

    int T = rd();
    while (T--) {
        int n = rd(), k = rd();
        ll ans = 0;
        for (int i = 0; i <= min(n, k); ++i) {
            ll term = C(n, i) * modpow(k - i, n - 1) % MOD;
            if (i & 1) ans = (ans - term + MOD) % MOD;
            else ans = (ans + term) % MOD;
        }
        ll denom = modpow(modpow(2, n) * 1LL * n % MOD, MOD - 2);
        ans = ans * fac[2 * n] % MOD * denom % MOD;
        cout << ans << '\n';
    }

    return 0;
}