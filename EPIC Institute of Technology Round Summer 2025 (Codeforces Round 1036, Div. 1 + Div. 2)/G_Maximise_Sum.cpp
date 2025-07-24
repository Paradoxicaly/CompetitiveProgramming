/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

const int N = 1e6 + 5;
int n, a[N], st[N], mn[N];
ll ans[N], smn[N];
pii gu[N];

ll query(int l, int r) {
	if (l >= r) return -1;
	ll sum = smn[l - 1];
	int tp = a[l] + a[r];
	int m = min(mn[l - 1], tp);
	sum += m;
	for (int i = l + 1; i < r; ++i) {
		m = min(m, a[i]);
		if (m == mn[i])
			return sum + smn[r - 1] - smn[i - 1];
		sum += m;
	}
	return sum;
}

void solve() {
	cin >> n;
	rep(i, n) cin >> a[i + 1];

	mn[0] = 2 * n;
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		mn[i] = min(mn[i - 1], a[i]);
		if (mn[i] == a[i]) st[++top] = i;
		smn[i] = smn[i - 1] + mn[i];
	}

	int cnt = 0;
	st[top + 1] = n + 1;
	for (int i = 1; i <= top; ++i) {
		int x = st[i];
		int v1 = mn[x - 1] - a[x];
		if (i == 1) v1 = n;
		int v2 = st[i + 1] - st[i];
		gu[++cnt] = {min(1LL * n, 1LL * v1 * v2), x};
	}
	sort(gu + 1, gu + cnt + 1);

	rep(i, n) ans[i] = 0;
	for (int i = 1; i <= n; ++i) ans[0] += mn[i];

	for (int i = n, mx = -1; i; --i) {
		if (a[i] <= mx) continue;
		mx = a[i];
		for (int j = cnt; j; --j) {
			if (gu[j].fi < a[i]) break;
			ans[i - gu[j].se] = max(ans[i - gu[j].se], query(gu[j].se, i));
		}
	}

	for (int i = n - 2; i >= 0; --i)
		ans[i] = max(ans[i], ans[i + 1]);

	rep(i, n) cout << ans[i] << " \n"[i + 1 == n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}