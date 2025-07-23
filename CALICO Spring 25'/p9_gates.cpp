/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define fi first
#define se second

template <int MOD, int RT>
struct mint {
    static const int mod = MOD;
    static constexpr mint rt() { return RT; } // primitive root
    int v;
    explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(ll _v) : v(int(_v % MOD)) { if (v < 0) v += MOD; }

    mint& operator+=(mint o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int((ll)v * o.v % MOD); return *this; }

    friend mint pow(mint a, ll p) {
        mint res = 1;
        while (p) {
            if (p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }

    friend mint inv(mint a) {
        return pow(a, MOD - 2);
    }

    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
};

using mi = mint<1000000007, 5>;
using vl = vector<mi>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

void solve() {
    int n;
    cin >> n;
    vector<int> vals(n);
    for (auto &x : vals) cin >> x;

    vvvl dp(n, vvl(n, vl(6))); // dp[start][end][state]

    rep(i, n) {
        if (vals[i] == 0) dp[i][i][0] = 1;
        else dp[i][i][1] = 1;
        dp[i][i][2] = 1;
        dp[i][i][5] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int start = 0; start + len - 1 < n; ++start) {
            int end = start + len - 1;
            int val = vals[end];

            mi z = dp[start][end - 1][0];
            mi o = dp[start][end - 1][1];
            mi zs0 = dp[start][end - 1][2];
            mi os0 = dp[start][end - 1][3];
            mi zs1 = dp[start][end - 1][4];
            mi os1 = dp[start][end - 1][5];

            if (val == 0) {
                dp[start][end][0] += 3 * z + o;
                dp[start][end][1] += 2 * o;
                dp[start][end][2] += 3 * zs0 + os0;
                dp[start][end][3] += 2 * os0;
                dp[start][end][4] += 3 * zs1 + os1;
                dp[start][end][5] += 2 * os1;
            } else {
                dp[start][end][0] += z + o;
                dp[start][end][1] += 2 * z + 2 * o;
                dp[start][end][2] += zs0 + os0;
                dp[start][end][3] += 2 * zs0 + 2 * os0;
                dp[start][end][4] += zs1 + os1;
                dp[start][end][5] += 2 * zs1 + 2 * os1;
            }
        }
    }

    mi ans = 0;
    rep(start, n) {
        for (int end = start; end < n; ++end) {
            mi z = dp[start][end][0], o = dp[start][end][1];
            mi lz, lo;

            if (start == 0) {
                lz = z;
                lo = o;
            } else {
                mi lz0 = dp[0][start - 1][0];
                mi lo0 = dp[0][start - 1][1];
                lz = 3 * lz0 * z + lz0 * o + lo0 * z + lo0 * o;
                lo = 2 * lo0 * o + 2 * lz0 * o + 2 * lo0 * z;
            }

            if (end == n - 1) {
                ans += lo;
            } else {
                ans += dp[end + 1][n - 1][3] * lz + dp[end + 1][n - 1][5] * lo;
            }
        }
    }

    cout << (int)ans << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}