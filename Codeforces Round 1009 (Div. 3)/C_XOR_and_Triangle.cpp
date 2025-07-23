/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

using ll = long long;
#define int long long
#define fi first
#define se second
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

void solve() {
    int x;
    cin >> x;
    int t = x;
    vector<int> b;
    while (x > 0) {
        b.pb(x % 2);
        x /= 2;
    }

    int ans = 0;
    bool flg = false;
    int cnt = 0;
    rep(i, b.size()) if (b[i] == 1) cnt++;

    rep(i, b.size()) {
        if (ans == 0) {
            if (b[i] == 1) ans -= (1LL << i);
            else ans += (1LL << i);
        }
        if (ans < 0 && b[i] == 0) {
            ans = -ans;
            ans += (1LL << i);
            flg = true;
            break;
        }
        if (ans > 0 && b[i] == 1) {
            ans += (1LL << i);
            flg = true;
            break;
        }
    }

    if (flg && cnt > 1) {
        cout << ans << '\n';
    } else {
        cout << -1 << '\n';
    }
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}