/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> pos(n * m + 1);
    rep(i, n) {
        rep(j, m) {
            int val;
            cin >> val;
            pos[val] = {i, j};
        }
    }

    int cur_x = 0, cur_y = 0, tot = 0;
    for (int k = 1; k <= n * m; ++k) {
        auto [x, y] = pos[k];
        int dx = min(abs(cur_x - x), n - abs(cur_x - x));
        int dy = min(abs(cur_y - y), m - abs(cur_y - y));
        tot += dx + dy;
        cur_x = x;
        cur_y = y;
    }

    cout << tot << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}