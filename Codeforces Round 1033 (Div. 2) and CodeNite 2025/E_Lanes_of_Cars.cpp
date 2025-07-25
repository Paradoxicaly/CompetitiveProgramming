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

void solve() {
	int n, k;
	cin >> n >> k;
	vi a(n);
	for (auto& x : a) cin >> x;
	sort(all(a));

	auto check = [&](int y) {
		ll moved = 0, spots = 0;
		for (auto& x : a) {
			moved += max(0, x - y);
			spots += max(0, y - k - x);
		}
		return moved <= spots;
	};

	int lo = 0, hi = 1e6 + 5;
	while (hi - lo > 1) {
		int mid = (lo + hi) / 2;
		if (check(mid)) hi = mid;
		else lo = mid;
	}
	int mxa = hi;
	ll moved = 0;
	for (auto& x : a) {
		int d = max(0, x - mxa);
		moved += d;
		x -= d;
	}
	ll ans = moved * k;

	lo = 0, hi = 1e6 + 5;
	while (hi - lo > 1) {
		int mid = (lo + hi) / 2;
		ll cost = 0;
		for (auto& x : a) cost += max(0, mid - x);
		if (cost <= moved) lo = mid;
		else hi = mid;
	}
	for (auto& x : a) {
		int d = max(0, lo - x);
		x += d;
		moved -= d;
	}
	assert(moved >= 0);
	for (auto& x : a) {
		if (x <= lo + 1 && moved > 0) {
			x++;
			moved--;
		}
	}
	assert(moved == 0);
	for (auto& x : a) {
		ans += 1LL * x * (x + 1) / 2;
	}
	sort(all(a));
	vi b = a;
	reverse(all(b));
	while (!a.empty() && !b.empty()) {
		if (a.back() <= b.back() + k + 1) {
			b.pop_back();
			continue;
		}
		ans -= a.back() - b.back() - k - 1;
		a.pop_back();
		b.back()++;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}