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
        int n, x;
        cin >> n >> x;
        vector<int> skills(n);
        rep(i, n) cin >> skills[i];

        sort(skills.rbegin(), skills.rend());

        int curr = 0, teams = 0;
        rep(i, n) {
            curr++;
            if (1LL * skills[i] * curr >= x) {
                teams++;
                curr = 0;
            }
        }
        cout << teams << '\n';
    }
    return 0;
}