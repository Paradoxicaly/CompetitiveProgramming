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
#else
#define bug(x...) void(0)
#endif

const ll INF = (ll)4e18;

void solve() {
	int a, b;
	ll x, y;
	cin >> a >> b >> x >> y;

	if (a == b) {
		cout << 0 << '\n';
		return;
	}

	int B = max(a, b), N = B + 2;
	vector<ll> dist(N + 1, INF);
	using Node = pair<ll, int>;
	priority_queue<Node, vector<Node>, greater<>> pq;

	dist[a] = 0;
	pq.push({0, a});

	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (d > dist[u]) continue;

		// 1) increment
		if (u + 1 <= N) {
			ll nd = d + x;
			if (nd < dist[u + 1]) {
				dist[u + 1] = nd;
				pq.push({nd, u + 1});
			}
		}

		// 2) LSB flip
		if ((u & 1) == 0) {
			if (u + 1 <= N) {
				ll nd = d + y;
				if (nd < dist[u + 1]) {
					dist[u + 1] = nd;
					pq.push({nd, u + 1});
				}
			}
		} else {
			if (u - 1 >= 0) {
				ll nd = d + y;
				if (nd < dist[u - 1]) {
					dist[u - 1] = nd;
					pq.push({nd, u - 1});
				}
			}
		}
	}

	cout << (dist[b] >= INF ? -1 : dist[b]) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}