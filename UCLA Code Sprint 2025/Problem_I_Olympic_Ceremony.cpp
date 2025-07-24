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

void flush() {
    cout.flush();
}

int ask(const vector<int>& q) {
    cout << "? ";
    for (int x : q) cout << x << ' ';
    cout << '\n';
    flush();
    string resp;
    int res;
    cin >> resp >> res;
    return res;
}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> groups;

    for (int i = 1; i <= n; ++i) {
        bool found = false;
        for (auto& g : groups) {
            vector<int> q = g;
            q.pb(i);
            int before = ask(g);
            int after = ask(q);
            if (after == before) {
                g.pb(i);
                found = true;
                break;
            }
        }
        if (!found) groups.pb({i});
    }

    vector<int> ans;
    for (auto& g : groups) for (int x : g) ans.pb(x);

    cout << "! ";
    for (int x : ans) cout << x << ' ';
    cout << '\n';
    flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}