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

template <typename T, int ND> struct tensor_view {
	array<int, ND> shape, strides;
	T* data;
	tensor_view(array<int, ND> s, array<int, ND> st, T* d) : shape(s), strides(st), data(d) {}
	tensor_view() : shape{0}, strides{0}, data(nullptr) {}
	int flatten(array<int, ND> idx) const {
		int r = 0;
		rep(i, ND) r += idx[i] * strides[i];
		return r;
	}
	T& operator[](array<int, ND> idx) const { return data[flatten(idx)]; }
	template <int D = ND> enable_if_t<(D > 0), tensor_view<T, ND-1>> operator[](int i) const {
		array<int, ND-1> ns, ns2;
		copy(all(shape) + 1, ns.begin());
		copy(all(strides) + 1, ns2.begin());
		return tensor_view<T, ND-1>(ns, ns2, data + strides[0] * i);
	}
};

template <typename T, int ND> struct tensor {
	array<int, ND> shape, strides;
	int len;
	T* data;
	tensor() : shape{0}, strides{0}, len(0), data(nullptr) {}
	tensor(array<int, ND> s, const T& t = T()) {
		shape = s, len = 1;
		for (int i = ND - 1; i >= 0; --i)
			strides[i] = len, len *= s[i];
		data = new T[len]; fill(data, data + len, t);
	}
	~tensor() { delete[] data; }
	using view_t = tensor_view<T, ND>;
	operator view_t() const { return view_t(shape, strides, data); }
	T& operator[](array<int, ND> idx) { return operator view_t()[idx]; }
	template <int D = ND> enable_if_t<(D > 0), tensor_view<T, ND-1>> operator[](int i) {
		return operator view_t()[i];
	}
};

template <typename T> T mod_inv_in_range(T a, T m) {
	T x = a, y = m, vx = 1, vy = 0;
	while (x) {
		T k = y / x;
		y %= x;
		vy -= k * vx;
		swap(x, y); swap(vx, vy);
	}
	assert(y == 1);
	return vy < 0 ? m + vy : vy;
}

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	int v;
	modnum() : v(0) {}
	modnum(ll x) : v(int(x % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend ostream& operator<<(ostream& os, const modnum& m) { return os << m.v; }
	friend istream& operator>>(istream& is, modnum& m) { ll x; is >> x; m = modnum(x); return is; }
	modnum inv() const { return modnum(mod_inv_in_range(v, MOD)); }
	modnum& operator+=(const modnum& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
	modnum& operator-=(const modnum& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
	modnum& operator*=(const modnum& o) { v = int((ll)v * o.v % MOD); return *this; }
	modnum& operator/=(const modnum& o) { return *this *= o.inv(); }
	friend modnum operator+(modnum a, const modnum& b) { return a += b; }
	friend modnum operator-(modnum a, const modnum& b) { return a -= b; }
	friend modnum operator*(modnum a, const modnum& b) { return a *= b; }
	friend modnum operator/(modnum a, const modnum& b) { return a /= b; }
};

const int MOD = 998244353;
using mint = modnum<MOD>;

void solve() {
	int n, m;
	cin >> n >> m;
	tensor<mint, 2> dp({n + 1, m + 1});
	dp[{0, 0}] = 1;
	rep(i, n) {
		rep(j, m + 1) {
			if (j + 1 <= m) dp[{i + 1, j + 1}] += dp[{i, j}];
			dp[{i + 1, j}] += dp[{i, j}];
		}
	}
	mint total = 0;
	rep(j, m + 1) total += dp[{n, j}];
	cout << total << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}