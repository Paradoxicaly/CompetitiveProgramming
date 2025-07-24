/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

const int INF = 1e9;
const int LINF = 1e18;

const int N = 1e6 + 5;
int n, st, dist[N], w[N], tim[N], ans;
vector<int> g[N];
queue<int> q;

void getdist(int u, int p) {
	for (int v : g[u]) {
		if (v == p) continue;
		dist[v] = dist[u] + 1;
		getdist(v, u);
	}
}

void dfs(int u, int p, int k, bool inner, int height, int T, int d) {
	if (height < 0) {
		T = max(T, ((-height + 1) / 2) * 2 + k * 2 + d);
	}
	if (T <= dist[u]) {
		ans = max(ans, dist[u]);
	} else return;

	for (int v : g[u]) {
		if (v == p) continue;
		if (inner && w[u] != w[v]) {
			dfs(v, u, min(k, tim[v]), inner, height + w[v], T + 1, d + 1);
		} else {
			dfs(v, u, k, false, height + w[v], T + 1, d + 1);
		}
	}
}

void solve() {
	cin >> n >> st;
	vector<int> f(n + 1, -LINF);
	ans = 0;

	rng(i, 1, n + 1) {
		dist[i] = 0;
		tim[i] = INF;
		g[i].clear();
	}
	rng(i, 1, n + 1) cin >> w[i];
	rep(i, n - 1) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}

	getdist(1, -1);

	rng(i, 1, n + 1) {
		for (int v : g[i]) {
			if (w[i] == 1 && w[v] == 1) {
				tim[i] = 0;
				q.push(i);
				break;
			}
		}
	}

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) {
			if (tim[v] == INF && w[v] != w[u]) {
				tim[v] = tim[u] + 1;
				q.push(v);
			}
		}
	}

	dfs(st, -1, tim[st], true, w[st], 1, 1);
	cout << ans + (dist[st] & 1) - 1 << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}