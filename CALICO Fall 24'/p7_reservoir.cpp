/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define ll long long
#define int ll
#define endl '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define forn(i,a,b) for(int i = a; i <= b; ++i)

using pii = pair<int,int>;
using pipii = pair<int, pii>;

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

	forn(i, 1, n) {
		forn(j, 1, m) {
			cin >> grid[i][j];
			compress[grid[i][j]] = 0;
			values.pb({grid[i][j], {i, j}});
		}
	}

	int idx = 0;
	for (auto &x : compress) x.second = idx++;

	vector<vector<pii>> ordered(idx + 1);
	for (auto &v : values) {
		v.first = compress[v.first];
		ordered[v.first].pb(v.second);
	}

	int gridSize = (n + 10) * (m + 10);
	par.resize(gridSize);
	act.assign(gridSize, 0);
	iota(par.begin(), par.end(), 0);

	int ans = 0, cur = 0;
	reverse(all(ordered));
	for (auto &group : ordered) {
		for (auto &[x, y] : group) {
			int current_id = id(x, y);
			act[current_id] = 1;
			int merges = 0;
			merges += unite(current_id, id(x-1, y));
			merges += unite(current_id, id(x+1, y));
			merges += unite(current_id, id(x, y-1));
			merges += unite(current_id, id(x, y+1));
			cur += 1 - merges;
		}
		ans = max(ans, cur);
	}
	cout << ans << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}