/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
#define fi first
#define se second
#define pb push_back
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MAXN = 400;
ll cost[MAXN];
vector<vector<ll>> dp;
int n;

ll f(int a, int b) {
    ll &ans = dp[a][b];
    if (ans != -1) return ans;

    int cnt = b - a + 1;
    if (b < a) cnt = (n - a) + b + 1;
    if (cnt < 3) return 0;

    ans = 0;
    for (int i = (a + 1) % n; i != b; i = (i + 1) % n) {
        ll cand = cost[a] * cost[b] * cost[i];
        if ((a + 1) % n != i)
            cand += f((a + 1) % n, (i - 1 + n) % n);
        if ((i + 1) % n != b)
            cand += f((i + 1) % n, (b - 1 + n) % n);
        ans = max(ans, cand);
    }

    ans = max({ans, f((a + 1) % n, b), f(a, (b - 1 + n) % n)});

    for (int i = (a + 1) % n; i != b; i = (i + 1) % n) {
        ans = max(ans, f(a, i) + f((i + 1) % n, b));
    }

    return ans;
}

void solve() {
    cin >> n;
    dp.assign(n, vector<ll>(n, -1));
    rep(i, n) cin >> cost[i];
    cout << f(0, n - 1) << '\n';
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}