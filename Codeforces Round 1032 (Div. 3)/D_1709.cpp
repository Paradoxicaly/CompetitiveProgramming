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
	int n;
	cin >> n;
	vi a(n), b(n);
	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	vector<pii> ans;
	rep(i, n) {
		if (a[i] > b[i]) {
			ans.emplace_back(3, i);
			swap(a[i], b[i]);
		}
	}

	auto go = [&](vi vec, int op) {
		rep(i, n) {
			rep(j, n - 1) {
				if (vec[j] > vec[j + 1]) {
					ans.emplace_back(op, j);
					swap(vec[j], vec[j + 1]);
				}
			}
		}
		assert(is_sorted(all(vec)));
	};

	go(a, 1);
	go(b, 2);

	cout << sz(ans) << '\n';
	for (auto [x, y] : ans)
		cout << x << ' ' << y + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}