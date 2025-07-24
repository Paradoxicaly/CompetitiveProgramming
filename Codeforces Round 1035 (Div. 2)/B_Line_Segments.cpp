/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

void solve() {
	ll n, px, py, qx, qy;
	cin >> n >> px >> py >> qx >> qy;
	ll dist_sq = (px - qx) * (px - qx) + (py - qy) * (py - qy);
	ll sum = 0, mx = 0;
	rep(i, n) {
		ll a;
		cin >> a;
		sum += a;
		mx = max(mx, a);
	}
	ll lo = max(0LL, 2 * mx - sum);
	ll hi = sum;

	if (lo * lo <= dist_sq && dist_sq <= hi * hi) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
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