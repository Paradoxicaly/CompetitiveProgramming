/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int wrapDist(int a, int b, int mod) {
    return min({abs(a - b), abs(a - b + mod), abs(a - b - mod)});
}

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    map<int, pair<int, int>> d;
    rep(i, n) rep(j, m) {
        int x;
        cin >> x;
        d[x] = {i, j};
    }

    int curx = 0, cury = 0;
    ll ans = 0;
    int idx = 0;

    for (auto &[val, pos] : d) {
        auto [x, y] = pos;

        int aux = 0;
        while (wrapDist(curx, x, n) + wrapDist(cury, y, m) > aux) {
            char move = s[idx];
            if (move == 'U') curx = (curx + n - 1) % n;
            else if (move == 'D') curx = (curx + 1) % n;
            else if (move == 'L') cury = (cury + m - 1) % m;
            else if (move == 'R') cury = (cury + 1) % m;
            idx = (idx + 1) % s.size();
            ++aux;
        }

        ans += aux;
        curx = x;
        cury = y;
    }

    cout << ans << '\n';
}

int main() {
    cincout();
    int tc;
    cin >> tc;
    while (tc--) solve();
    return 0;
}