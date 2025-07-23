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

const int MAX = 5 << 17;
string S;
int imos[MAX];
int cost[MAX];
ll dp[MAX];

ll g(ll p) {
    int n = S.size();
    rep(i, n + 1) dp[i] = 1e18;
    dp[0] = 0;
    rep(i, n) {
        dp[i + 1] = min(dp[i + 1], dp[i]);
        if (i + 6 <= n) {
            dp[i + 6] = min(dp[i + 6], dp[i] + cost[i] - p);
        }
    }
    return dp[n];
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) {
        cin >> S;
        int mx = S.size() / 6;
        rep(i, mx + 2) imos[i] = 0;

        int n;
        cin >> n;
        while (n--) {
            int l, r;
            cin >> l >> r;
            r = min(r, mx);
            if (l <= r) {
                imos[l]++;
                imos[r + 1]--;
            }
        }

        int MAXv = 0;
        rep(i, mx + 1) {
            imos[i + 1] += imos[i];
            MAXv = max(MAXv, imos[i]);
        }

        int orig = 0;
        int len = S.size();
        if (len >= 6) {
            rep(i, len - 5) {
                cost[i] = 0;
                rep(j, 6) {
                    if (S[i + j] != "docker"[j]) cost[i]++;
                }
                if (cost[i] == 0) orig++;
            }
        }

        ll ans = 1e9;
        for (int u = orig; u >= 0; --u) {
            if (imos[u] == MAXv) {
                ans = min(ans, (ll)(orig - u));
            }
        }

        int v = orig;
        while (v <= mx && imos[v] != MAXv) v++;

        if (orig < v && v <= mx) {
            ll L = -1e10, R = 1e10;
            while (R - L > 1) {
                ll p = (L + R) / 2;
                if (v <= g(p) - g(p + 1)) R = p;
                else L = p;
            }
            ans = min(ans, g(R) + R * v);
        }

        cout << ans << '\n';
    }
    return 0;
}