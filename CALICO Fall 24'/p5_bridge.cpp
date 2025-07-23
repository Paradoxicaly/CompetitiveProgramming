/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()
#define pb push_back

const int MAXN = 1e5 + 5;
int b, n;
int arr[MAXN];

bool check(int h) {
    int cost = 0;
    rep(i, n) {
        if (arr[i] > h) cost += arr[i] - h;
        if (cost > b) return false;
    }
    return true;
}

void solve() {
    cin >> b >> n;
    rep(i, n) cin >> arr[i];

    int l = 0, r = 1e13, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    sort(arr, arr + n);
    cout << max(ans, arr[0]) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}