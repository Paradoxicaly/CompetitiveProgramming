/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define int long long
#define endl '\n'
#define pb push_back
#define pii pair<int, int>
#define pipii pair<int, pii>
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define fastinput ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, m;
vector<int> par, act;

int id(int i, int j) {
    return i * (m + 2) + j;
}

int root(int x) {
    return par[x] == x ? x : par[x] = root(par[x]);
}

int unite(int a, int b) {
    a = root(a);
    b = root(b);
    if (!act[a] || !act[b]) return 0;
    if (a == b) return 0;
    if (b > a) swap(a, b);
    par[a] = b;
    return 1;
}

void solve() {
    cin >> n >> m;
    vector<vector<int>> grid(n + 2, vector<int>(m + 2, 0));
    vector<pipii> values;
    map<int, int> compress;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            compress[grid[i][j]] = 0;
            values.pb({grid[i][j], {i, j}});
        }
    }

    int idx = 0;
    for (auto& [val, _] : compress) {
        compress[val] = idx++;
    }

    vector<vector<pii>> grouped(idx);
    for (auto& [val, pos] : values) {
        grouped[compress[val]].pb(pos);
    }

    int gridSize = (n + 10) * (m + 10);
    par.resize(gridSize);
    act.assign(gridSize, 0);
    iota(all(par), 0);

    int ans = 0, curr = 0;
    reverse(all(grouped));
    for (auto& vec : grouped) {
        for (auto [x, y] : vec) {
            int p = id(x, y);
            act[p] = 1;
            int merges = 0;
            merges += unite(p, id(x - 1, y));
            merges += unite(p, id(x + 1, y));
            merges += unite(p, id(x, y - 1));
            merges += unite(p, id(x, y + 1));
            curr += 1 - merges;
        }
        ans = max(ans, curr);
    }

    cout << ans << endl;
}

int32_t main() {
    fastinput;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}