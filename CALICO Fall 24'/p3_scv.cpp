/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()
using str = string;

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

str identifyShape(vector<str>& grid, int n, int m) {
    int top = -1, bottom = -1, left = -1, right = -1;

    rep(i, n) {
        rep(j, m) {
            if (grid[i][j] == '#') {
                if (top == -1) top = i;
                bottom = i;
                if (left == -1 || j < left) left = j;
                if (j > right) right = j;
            }
        }
    }

    bool isRectangle = true;
    for (int i = top; i <= bottom; ++i) {
        for (int j = left; j <= right; ++j) {
            if (grid[i][j] != '#') {
                isRectangle = false;
                break;
            }
        }
        if (!isRectangle) break;
    }

    return isRectangle ? "ferb" : "phineas";
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<str> grid(n);
    rep(i, n) cin >> grid[i];
    cout << identifyShape(grid, n, m) << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}