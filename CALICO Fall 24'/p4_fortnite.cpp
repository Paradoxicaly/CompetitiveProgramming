/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);
}

void solve() {
    ld n, h, d, s, p;
    cin >> n >> h >> d >> s >> p;

    h -= p;
    d /= s;

    if (n >= d * p) {
        cout << d << '\n';
    } else if (h > 0) {
        cout << d + (d * p - n) / h << '\n';
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