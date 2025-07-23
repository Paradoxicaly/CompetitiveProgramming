/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

struct Competitor {
    string name;
    int power;
};

void solve() {
    int n;
    cin >> n;
    vector<string> names(n);
    vector<int> powers(n);
    rep(i, n) cin >> names[i];
    rep(i, n) cin >> powers[i];

    vector<Competitor> current;
    rep(i, n) current.pb({names[i], powers[i]});

    while (current.size() > 1) {
        vector<Competitor> next;
        for (size_t i = 0; i < current.size(); i += 2) {
            Competitor a = current[i];
            Competitor b = current[i + 1];
            if (a.power > b.power) {
                a.power += b.power;
                next.pb(a);
            } else if (b.power > a.power) {
                b.power += a.power;
                next.pb(b);
            } else {
                next.pb({a.name + b.name, a.power + b.power});
            }
        }
        current = move(next);
    }

    cout << current[0].name << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}