/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
#define fi first
#define se second
#define pb push_back

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

bool canFormSquare(int l, int r, int d, int u) {
    if (l != r || d != u || l != d) return false;

    vector<pii> points = {
        {-l, 0},
        {r, 0},
        {0, -d},
        {0, u}
    };

    vector<double> dist;
    rep(i, 4) {
        for (int j = i + 1; j < 4; j++) {
            int dx = points[i].fi - points[j].fi;
            int dy = points[i].se - points[j].se;
            dist.pb(sqrt(dx * dx + dy * dy));
        }
    }

    sort(all(dist));

    rep(i, 1) {
        if (abs(dist[0] - dist[i]) > 1e-9) return false;
    }

    rep(i, 3) {
        if (abs(dist[i] - dist[0]) > 1e-9) return false;
    }

    if (abs(dist[4] - dist[5]) > 1e-9) return false;
    if (abs(dist[4] / dist[0] - sqrt(2.0)) > 1e-9) return false;

    return true;
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) {
        int l, r, d, u;
        cin >> l >> r >> d >> u;
        cout << (canFormSquare(l, r, d, u) ? "Yes" : "No") << '\n';
    }
    return 0;
}