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

void solve() {
	int n, m;
	cin >> n >> m;
	vector a(n, vector<int>(m));
	int mx = 0;
	rep(i, n) rep(j, m) {
		cin >> a[i][j];
		mx = max(mx, a[i][j]);
	}
	vi row(n), col(m);
	int tot = 0;
	rep(i, n) rep(j, m) {
		if (a[i][j] == mx) {
			a[i][j] = 1;
			row[i]++, col[j]++, tot++;
		} else {
			a[i][j] = 0;
		}
	}
	rep(i, n) rep(j, m) {
		if (row[i] + col[j] - a[i][j] == tot) {
			cout << mx - 1 << '\n';
			return;
		}
	}
	cout << mx << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}