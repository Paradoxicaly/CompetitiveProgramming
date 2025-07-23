/*
Derrick (Tomato_Cultivator)
*/
 
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using pii = pair<int, int>;
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
 
int solve() {
    int n, m;
    cin >> n >> m;
    vector<int> pos(n), rad(n);
    rep(i, n) cin >> pos[i];
    rep(i, n) cin >> rad[i];

    vector<vector<pii>> intervals(2 * m + 1);
    rep(i, n) {
        for (ll y = -rad[i]; y <= rad[i]; ++y) {
            ll dy = y * y;
            ll dx2 = 1LL * rad[i] * rad[i] - dy;
            if (dx2 < 0) continue; // due to rounding errors
            ll dx = sqrtl(dx2);
            int lowx = int(pos[i] - dx);
            int highx = int(pos[i] + dx);
            intervals[y + m].pb({lowx, highx});
        }
    }

    ll ans = 0;
    for (auto &arr : intervals) {
        int high = INT_MIN;
        sort(all(arr));
        for (auto &[l, r] : arr) {
            if (l <= high) {
                ans += max(0LL, ll(r - high));
                high = max(high, r);
            } else {
                ans += r - l + 1;
                high = r;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
 
int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}