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

const ll MOD = 998244353;

void upd(ll& x, ll inc) {
    x = (x + inc) % MOD;
}

struct Solver {
    int n, k;
    vector<vector<int>> v;

    void solve() {
        cin >> n >> k;
        v = vector<vector<int>>(2, vector<int>(n));
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < n; ++j)
                cin >> v[i][j];

        ll ans = 1;
        if (v[0][0] == -1) ans = (ans * k) % MOD;
        if (v[1][n - 1] == -1) ans = (ans * k) % MOD;

        vector<vector<ll>> dp(n, vector<ll>(k + 1));
        dp[0][k] = 1;

        for (int i = 1; i < n; ++i) {
            vector<int> diffs(2 * k - 1);

            if (v[0][i] != -1) {
                if (v[1][i - 1] != -1) {
                    diffs[v[0][i] - v[1][i - 1] + k - 1]++;
                } else {
                    for (int j = 1; j <= k; ++j)
                        diffs[v[0][i] - j + k - 1]++;
                }
            } else {
                if (v[1][i - 1] != -1) {
                    for (int j = 1; j <= k; ++j)
                        diffs[j - v[1][i - 1] + k - 1]++;
                } else {
                    for (int j = -k + 1; j < k; ++j)
                        diffs[j + k - 1] = k - abs(j);
                }
            }

            for (int j = -k + 1; j < 0; ++j) {
                for (int l = 0; l < k; ++l)
                    upd(dp[i][-j], dp[i - 1][l] * diffs[j + k - 1] % MOD);
                upd(dp[i][-j], dp[i - 1][k] * diffs[j + k - 1] % MOD);
            }

            for (int j = 0; j < k; ++j) {
                for (int l = j; l < k; ++l)
                    upd(dp[i][l - j], dp[i - 1][l] * diffs[j + k - 1] % MOD);
                upd(dp[i][k], dp[i - 1][k] * diffs[j + k - 1] % MOD);
            }
        }

        ll ans2 = 0;
        for (int i = 0; i <= k; ++i)
            upd(ans2, dp[n - 1][i]);

        cout << (ans * ans2) % MOD << "\n";
    }
};

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) {
        Solver solver;
        solver.solve();
    }
    return 0;
}