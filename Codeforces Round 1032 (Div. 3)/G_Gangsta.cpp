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
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif

const int mod = 998244353, N = 1 << 19;

template <typename T>
struct BIT {
	vector<T> val;
	int n, offset;
	BIT () = default;
	BIT (int _n, int _offset = 3) : n(_n + _offset * 2), offset(_offset) {
		val.assign(n, 0);
	}
	void add(int p, T v) {
		for (p += offset; p < n; p += p & -p) val[p] += v;
	}
	T query(int p) {
		T ans = 0;
		for (p += offset; p > 0; p -= p & -p) ans += val[p];
		return ans;
	}
	T query(int l, int r) {
		return query(r - 1) - query(l - 1);
	}
	int kth(int k) {
		int ans = 0;
		for (int i = 1 << __lg(n); i > 0; i >>= 1)
			if (ans + i < n && val[ans + i] < k)
				k -= val[ans += i];
		return ans - offset + 1;
	}
};

void solve() {
	int n;
	string s;
	cin >> n >> s;
	ll ans = 0;
	rep(iter, 2) {
		int pre = 0;
		BIT<ll> bit1(2 * n + 10, n + 2), bit2(2 * n + 10, n + 2);
		bit1.add(pre, 1);
		bit2.add(pre, pre);
		rep(i, n) {
			pre += ((s[i] == '0') ^ iter ? 1 : -1);
			ans += bit1.query(pre) * pre - bit2.query(pre);
			bit1.add(pre, 1);
			bit2.add(pre, pre);
		}
	}
	bug(ans);
	rng(i, 1, n + 1) ans += 1ll * i * (n - i + 1);
	cout << ans / 2 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}