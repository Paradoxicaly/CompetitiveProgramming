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

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) {
        ll l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        ll ans = 0;

        for (int k = 0; k <= 20; ++k) {
            ll p = 1LL << k;

            ll amin1 = (l1 + p - 1) / p;
            ll amax1 = r1 / p - 1;
            ll A = (amax1 >= amin1) ? amax1 - amin1 + 1 : 0;

            ll bmin1 = (l2 + p - 1) / p;
            ll bmax1 = r2 / p - 1;
            ll B = (bmax1 >= bmin1) ? bmax1 - bmin1 + 1 : 0;

            ll A1 = 0, B1 = 0;
            if (k < 20) {
                ll p1 = 1LL << (k + 1);

                ll amin2 = (l1 + p1 - 1) / p1;
                ll amax2 = r1 / p1 - 1;
                A1 = (amax2 >= amin2) ? amax2 - amin2 + 1 : 0;

                ll bmin2 = (l2 + p1 - 1) / p1;
                ll bmax2 = r2 / p1 - 1;
                B1 = (bmax2 >= bmin2) ? bmax2 - bmin2 + 1 : 0;
            }

            ans += A * B - 4 * A1 * B1;
        }

        cout << ans << '\n';
    }
    return 0;
}