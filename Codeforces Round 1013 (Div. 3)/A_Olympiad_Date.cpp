/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define fi first
#define se second
#define pb push_back

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
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
        int n;
        cin >> n;
        vector<int> count(10, 0);
        int ans = 0;
        rep(i, n) {
            int d;
            cin >> d;
            count[d]++;
            if (count[0] >= 3 && count[1] >= 1 && count[2] >= 2 &&
                count[3] >= 1 && count[5] >= 1 && ans == 0) {
                ans = i + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}