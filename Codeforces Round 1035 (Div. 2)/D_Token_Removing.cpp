/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()

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

const int MAXN = 5001;
ll dp[MAXN], tdp[MAXN];

void solve() {
	ll n, mod;
	cin >> n >> mod;

	rep(i, n + 1) dp[i] = 0;
	dp[0] = 1;

	rep(i, n) {
		rep(j, n + 1) {
			if (j < n)
				tdp[j + 1] = (tdp[j + 1] + dp[j] * (i + 1)) % mod;
			tdp[j] = (tdp[j] + dp[j] * (((j + 1) * (i + 1)) + 1)) % mod;
			if (j > 0)
				tdp[j - 1] = (tdp[j - 1] + dp[j] * j) % mod;
		}
		rep(j, n + 1) {
			dp[j] = tdp[j];
			tdp[j] = 0;
		}
	}

	cout << dp[0] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}