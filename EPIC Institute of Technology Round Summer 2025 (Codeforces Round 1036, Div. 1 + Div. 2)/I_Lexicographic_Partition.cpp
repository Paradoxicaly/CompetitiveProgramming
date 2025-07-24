/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
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

template <typename T, typename F>
struct SparseTable {
	int n;
	vector<vector<T>> mat;
	F func;

	SparseTable(const vector<T>& a, const F& f) : func(f) {
		n = sz(a);
		int max_log = 32 - __builtin_clz(n);
		mat.resize(max_log);
		mat[0] = a;
		for (int j = 1; j < max_log; j++) {
			mat[j].resize(n - (1 << j) + 1);
			for (int i = 0; i <= n - (1 << j); i++) {
				mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	T get(int l, int r) const {
		assert(0 <= l && l <= r && r < n);
		int lg = 31 - __builtin_clz(r - l + 1);
		return func(mat[lg][l], mat[lg][r - (1 << lg) + 1]);
	}
};

void solve() {
	int n;
	cin >> n;
	vector<int> x(n);
	rep(i, n) cin >> x[i];

	SparseTable<int, function<int(int, int)>> st(x, [&](int i, int j) {
		return min(i, j);
	});

	vector<vector<int>> at(n + 1);
	rep(i, n) at[x[i]].pb(i);

	vector<int> v = {0}, u = {0}, pr(n, -1), ne(n, -1);
	auto link = [&](int l, int r, int i) {
		pr[i] = l;
		ne[i] = r;
		if (l != -1) ne[l] = i;
		if (r != -1) pr[r] = i;
	};

	bool fail = false;
	for (int i = 1; i < n; ++i) {
		if (x[i] > x[i - 1] + 1) {
			fail = true;
			break;
		}
		if (x[i] == x[i - 1] + 1) {
			int q = 0;
			auto it = lower_bound(all(at[x[i]]), i + 1);
			if (it != at[x[i]].end()) {
				int j = *it;
				if (st.get(i, j) >= x[i]) q = 1;
			}
			if (q == 1 && v.back() == 1) {
				fail = true;
				break;
			}
			if (q == 0) {
				link(pr[i - 1], i - 1, i);
			} else {
				link(i - 1, ne[i - 1], i);
			}
			v.pb(q);
			u.pb(i);
			continue;
		}
		if (v[x[i] - 1] == 0) {
			fail = true;
			break;
		}
		v.resize(x[i]);
		u.resize(x[i]);
		link(u.back(), ne[u.back()], i);
		u.back() = i;
	}

	if (fail) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	int root = find(all(pr), -1) - pr.begin();
	vector<int> a(n, -1);
	rep(i, n) {
		a[root] = i + 1;
		root = ne[root];
	}
	rep(i, n) cout << a[i] << " \n"[i + 1 == n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}