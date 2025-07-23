/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define inf 1e9
#define endl '\n'
#define fastinput ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

int scan(int v) {
    v++;
    cout << "SCAN " << v << endl;
    string response;
    cin >> response;
    if (response == "WRONG_ANSWER") exit(0);
    return stoi(response) - 1;
}

void sub(int d) {
    cout << "SUBMIT " << d << endl;
    string x;
    cin >> x;
    if (x == "WRONG_ANSWER") exit(0);
}

void solve() {
    const int n = 500;
    vector<set<int>> adj(n);
    vector<int> distFrom0(n, inf), distFrom499(n, inf);
    vector<vector<int>> bfs0(50), bfs499(50);

    distFrom0[0] = 0;
    distFrom499[499] = 0;
    bfs0[0].pb(0);
    bfs499[0].pb(499);

    for (int d = 0; d < n; ++d) {
        for (int u : bfs0[d]) {
            while (sz(adj[u]) < 3) {
                int v = scan(u);
                adj[u].insert(v);
                adj[v].insert(u);
            }
            for (int v : adj[u]) {
                if (distFrom499[v] != inf) {
                    sub(d + distFrom499[v] + 1);
                    return;
                }
                if (distFrom0[v] == inf) {
                    distFrom0[v] = d + 1;
                    bfs0[d + 1].pb(v);
                }
            }
        }

        for (int u : bfs499[d]) {
            while (sz(adj[u]) < 3) {
                int v = scan(u);
                adj[u].insert(v);
                adj[v].insert(u);
            }
            for (int v : adj[u]) {
                if (distFrom0[v] != inf) {
                    sub(d + distFrom0[v] + 1);
                    return;
                }
                if (distFrom499[v] == inf) {
                    distFrom499[v] = d + 1;
                    bfs499[d + 1].pb(v);
                }
            }
        }
    }
}

int32_t main() {
    fastinput;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}