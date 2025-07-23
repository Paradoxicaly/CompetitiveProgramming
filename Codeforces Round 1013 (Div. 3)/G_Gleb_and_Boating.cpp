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
        int s, k;
        cin >> s >> k;

        if (s % k == 0) {
            cout << k << '\n';
            continue;
        }

        if (s >= k * (k - 2)) {
            cout << max(1, k - 2) << '\n';
            continue;
        }

        int ans = k;
        vector<bool> a(s + 1, false), b(s + 1, false);
        for (int i = 0; i <= s; i += k) a[i] = true;

        while (ans > 2 && !a[s]) {
            ans -= 2;
            fill(all(b), false);
            for (int i = 0; i <= s; ++i) {
                if (a[i]) {
                    for (int j = i - ans - 1; j >= 0; j -= ans + 1)
                        b[j] = true;
                }
            }
            fill(all(a), false);
            for (int i = 0; i <= s; ++i) {
                if (b[i]) {
                    for (int j = i + ans; j <= s; j += ans)
                        a[j] = true;
                }
            }
        }

        cout << (a[s] ? ans : 1) << '\n';
    }
    return 0;
}