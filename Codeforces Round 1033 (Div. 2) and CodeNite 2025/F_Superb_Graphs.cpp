/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

#ifdef Tomato
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

using bs = bitset<305>;

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values;

	TwoSat(int n = 0) : N(n), gr(2 * n) {}

	int addVar() {
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void either(int f, int j) {
		f = max(2 * f, -1 - 2 * f);
		j = max(2 * j, -1 - 2 * j);
		gr[f].pb(j ^ 1);
		gr[j].pb(f ^ 1);
	}

	void setValue(int x) { either(x, x); }

	void atMostOne(const vi& li) {
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		rng(i, 2, sz(li)) {
			int nxt = addVar();
			either(cur, ~li[i]);
			either(cur, nxt);
			either(~li[i], nxt);
			cur = ~nxt;
		}
		either(cur, ~li[1]);
	}

	vi val, comp, z; int time = 0;

	int dfs(int i) {
		int low = val[i] = ++time, x;
		z.pb(i);
		for (int e : gr[i]) if (!comp[e])
			low = min(low, val[e] ? val[e] : dfs(e));
		if (low == val[i]) {
			do {
				x = z.back(); z.pop_back();
				comp[x] = low;
				if (values[x >> 1] == -1)
					values[x >> 1] = x & 1;
			} while (x != i);
		}
		return val[i] = low;
	}

	bool solve() {
		values.assign(N, -1);
		val.assign(2 * N, 0);
		comp = val;
		rep(i, 2 * N) if (!comp[i]) dfs(i);
		rep(i, N) if (comp[2 * i] == comp[2 * i + 1]) return false;
		return true;
	}
};

void solve() {
	int n, k;
	cin >> n >> k;
	TwoSat solver(n);
	rep(i, k) {
		vector<bs> G(n);
		int m;
		cin >> m;
		rep(_, m) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			G[u][v] = G[v][u] = 1;
		}
		rep(u, n) rng(v, u + 1, n) {
			if (G[u][v] && (G[u] ^ G[v]).count() == 2) {
				solver.either(~u, ~v);
			} else if (G[u] == G[v]) {
				solver.either(u, v);
			}
		}
	}
	cout << (solver.solve() ? "YES" : "NO") << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}