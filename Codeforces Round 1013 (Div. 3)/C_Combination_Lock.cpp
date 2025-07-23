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
        ll n;
        cin >> n;

        if (n == 1) {
            cout << "1\n";
            continue;
        }
        if (n == 3) {
            cout << "1 3 2\n";
            continue;
        }
        if (n == 4) {
            cout << "-1\n";
            continue;
        }
        if (n == 5) {
            cout << "4 1 3 5 2\n";
            continue;
        }
        if (n % 2 == 0) {
            cout << "-1\n";
            continue;
        }

        vector<ll> p(n);
        rng(i, 1, n + 1) {
            ll val = (2LL * i) % n;
            if (val == 0) val = n;
            p[i - 1] = val;
        }
        rep(i, n) cout << p[i] << (i + 1 < n ? ' ' : '\n');
    }
    return 0;
}