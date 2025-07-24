/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

const ll INF = (ll)4e18;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n + 1), b(n + 1);
	rng(i, 1, n) cin >> a[i];
	rng(i, 1, n + 1) cin >> b[i];
	a[n] = 0;

	vector<pair<int, ll>> f;
	f.emplace_back(0, 0);

	rng(i, 1, n + 1) {
		vector<pair<int, ll>> g;
		int prefix = 0;
		for (int bit = 30; bit >= -1; --bit) {
			int y = prefix | a[i - 1] | a[i];
			if (bit != -1) y |= (1 << bit);
			if (y >= b[i]) {
				ll best = INF;
				for (auto& [x, dp] : f) {
					if ((x & y) != a[i - 1]) continue;
					best = min(best, dp + (y - b[i]));
				}
				if (best < INF) g.emplace_back(y, best);
			}
			if (bit >= 0 && (b[i] & (1 << bit)))
				prefix |= (1 << bit);
		}
		f.swap(g);
	}

	ll ans = INF;
	for (auto& [_, cost] : f)
		ans = min(ans, cost);
	cout << (ans < INF ? ans : -1LL) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}