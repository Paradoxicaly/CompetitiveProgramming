/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

#ifdef Doludu
template <typename T>
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> team(n + 1);
    map<int, set<int>> team_members;
    rep(i, n) {
        cin >> team[i + 1];
        team_members[team[i + 1]].insert(i + 1);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int t, i;
            cin >> t >> i;
            int old = team[i];
            if (old != t) {
                team_members[old].erase(i);
                team_members[t].insert(i);
                team[i] = t;
            }
        } else {
            int t;
            cin >> t;
            if (sz(team_members[t]) <= 1) {
                cout << -1 << '\n';
                continue;
            }

            int others = 0, active_teams = 0;
            for (auto &[key, members] : team_members) {
                if (sz(members)) {
                    active_teams++;
                    if (key != t)
                        others += sz(members);
                }
            }

            if (active_teams == 1) {
                cout << 0 << '\n';
            } else {
                cout << others << '\n';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}