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

void solve() {
	ll n, l, r, k;
	cin >> n >> l >> r >> k;

	if (n % 2 == 1) {
		cout << l << '\n';
		return;
	}

	if (n == 2) {
		cout << "-1\n";
		return;
	}

	int i;
	for (i = 60; i >= 0; --i) {
		if ((r >> i) & 1) break;
	}
	if ((l >> i) & 1) {
		cout << "-1\n";
		return;
	}

	for (i = 60; i >= 0; --i) {
		if ((l >> i) & 1) break;
	}

	if (k <= n - 2) {
		cout << l << '\n';
	} else {
		cout << (1LL << (i + 1)) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}