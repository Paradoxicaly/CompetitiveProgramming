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
	int n, x;
	ll s;
	cin >> n >> s >> x;
	vi a(n);
	rep(i, n) cin >> a[i];

	auto count_subarrays = [&](int l, int r) {
		map<ll, ll> freq;
		ll sum = 0, res = 0;
		freq[0] = 1;
		rng(i, l, r) {
			sum += a[i];
			res += freq[sum - s];
			freq[sum]++;
		}
		return res;
	};

	auto range_calc = [&](int mx) {
		ll res = 0;
		for (int i = 0, j = 0; i < n; i = j) {
			if (a[j] > mx) {
				j++;
			} else {
				while (j < n && a[j] <= mx) j++;
				res += count_subarrays(i, j);
			}
		}
		return res;
	};

	cout << range_calc(x) - range_calc(x - 1) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}