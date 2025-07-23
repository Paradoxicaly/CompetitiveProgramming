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

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MOD = 998244353;
struct mint {
    int v;
    mint(ll x = 0) { v = int(x % MOD); if (v < 0) v += MOD; }
    mint& operator+=(const mint& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mint& operator-=(const mint& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mint& operator*=(const mint& o) { v = int(1LL * v * o.v % MOD); return *this; }
    mint operator+(const mint& o) const { return mint(*this) += o; }
    mint operator-(const mint& o) const { return mint(*this) -= o; }
    mint operator*(const mint& o) const { return mint(*this) *= o; }
    mint pow(ll n) const {
        mint res = 1, x = *this;
        while (n) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }
    mint inv() const { return pow(MOD - 2); }
    mint& operator/=(const mint& o) { return *this *= o.inv(); }
    mint operator/(const mint& o) const { return mint(*this) /= o; }
    int val() const { return v; }
};

const int MAX = 2 << 17;
mint dp[MAX];

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) {
        int n, x;
        cin >> n >> x;
        if (n == 1) {
            cout << x << '\n';
            continue;
        }
        if (1LL * n * (n + 1) / 2 > x + 1) {
            cout << "0\n";
            continue;
        }
        int L = x - n * (n + 1) / 2 + 1;
        rep(i, L + 1) dp[i] = 0;
        dp[0] = 1;
        for (int u = 1; u < n; ++u) {
            for (int i = 0; i + u <= L; ++i) {
                dp[i + u] += dp[i];
            }
        }
        mint ans = 0;
        rep(i, L + 1) {
            ans += dp[i] * (L - i + 1);
        }
        cout << ans.val() << '\n';
    }
    return 0;
}