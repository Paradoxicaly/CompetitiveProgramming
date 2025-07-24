/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define pii pair<int, int>
#define iii array<int, 3>
#define all(x) (x).begin(), (x).end()
#define len(x) ((int)(x).size())
#define F(i, x, y) for (int i = (x); i <= (y); ++i)
#define Fd(i, x, y) for (int i = (x); i >= (y); --i)
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
const int mod = 998244353;
const int inf = 1e18;

int n, m;

void solve() {
    cin >> n >> m;
    if (n == 1 || m == 1 || (n == 2 && m == 2)) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
    }
}

int32_t main() {
    fastio;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}