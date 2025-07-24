/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define fi first
#define se second
#define pb push_back
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rng(i, a, b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

int main() {
    cincout();

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<pii> pts;
    int c = 0;

    while (a.size() > 1) {
        sort(all(a));
        int x = a[0], y = a[1];

        rep(i, x + 1) pts.pb({c, -i});
        rep(i, y + 1) pts.pb({c + 1, i - y});

        c += 2;
        a.erase(a.begin());
        a.erase(a.begin());
        a.pb(x + y);
    }

    pts.pb({1000000, 1});
    cout << pts.size() << '\n';
    for (auto [x, y] : pts) {
        cout << x << ' ' << y << '\n';
    }

    return 0;
}