/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    ll tot = 0, curr = 1;
    rep(i, n) {
        if (s[i] == 'T') {
            tot += curr;
            curr = 1;
        } else {
            curr *= 2;
        }
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