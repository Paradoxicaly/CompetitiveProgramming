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
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

int query(int a, int b, int c) {
    cout << "? " << a << " " << b << " " << c << endl;
    int x;
    cin >> x;
    return x;
}

int solve() {
    int n;
    cin >> n;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<int> pts = {1, 2, 3};

    rep(i, 0, 75) {
        int x = query(pts[0], pts[1], pts[2]);
        if (x == 0) {
            cout << "! " << pts[0] << " " << pts[1] << " " << pts[2] << endl;
            return 0;
        }
        shuffle(all(pts), rng);
        pts[0] = x;
    }

    while (true) {}
    
    return 0;
}

int main() {
    cincout();
    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}