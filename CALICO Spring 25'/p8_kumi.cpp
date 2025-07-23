/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define pb push_back
#define fi first
#define se second

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

void solve() {
    ll n;
    cin >> n;

    ll x = ceil((1 + sqrt(8 * n + 1)) / 2.0);
    ll diff = x * (x - 1) / 2 - n;

    vector<ll> to_sub;
    while (diff > 0) {
        ll y = floor((1 + sqrt(8 * diff + 1)) / 2.0);
        diff -= y * (y - 1) / 2;
        to_sub.pb(y);
    }

    for (ll us : to_sub) {
        x -= us;
        while (us--) cout << 'u';
        cout << 'w';
    }

    while (x--) cout << "uw";
    cout << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}