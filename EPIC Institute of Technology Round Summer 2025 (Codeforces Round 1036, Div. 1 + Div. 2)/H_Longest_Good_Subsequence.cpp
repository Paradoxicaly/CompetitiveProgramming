/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using pii = pair<int, int>;

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

const i64 INF = 1001001001001001001;

template<typename T>
void chmin(T &a, const T &b) { if (b < a) a = b; }

template<typename T>
void chmax(T &a, const T &b) { if (a < b) a = b; }

void solve() {
	int N;
	cin >> N;
	vector<int> A(N + 2);
	rep(i, N) cin >> A[i + 1];
	N += 2;

	vector<vector<int>> poss(N);
	rep(i, N) poss[A[i]].pb(i);

	vector<int> posi(N);
	for (auto &v : poss)
		rep(i, sz(v)) posi[v[i]] = i;

	if (poss[0].empty()) {
		cout << "0\n";
		return;
	}

	vector<vector<int>> dp(N);
	vector<int> vis(N, N), sub(N + 1);

	for (int s = N - 1; s >= 0; --s) {
		rng(t, s, N + 1) sub[t] = 0;
		int a = A[s];
		vector<int> res(sz(poss[a]) - posi[s]);
		sub[s] = a + 1;

		for (int i = s + 1; i < N; ++i) {
			chmax(sub[i], sub[i - 1]);
			if (A[i] == a) {
				chmax(sub[i], sub[i - 1] + 1);
			} else if (A[i] > a && A[i] <= sub[i - 1] && vis[A[i]] != s) {
				vis[A[i]] = s;
				rep(d, sz(dp[i])) {
					chmax(sub[poss[A[i]][d + posi[i]]], dp[i][d]);
				}
			}
		}

		for (int d = posi[s]; d < sz(poss[a]); ++d)
			res[d - posi[s]] = sub[poss[a][d]];

		swap(dp[s], res);
	}

	cout << (dp[0][1] - 2) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	rep(t, T) solve();
	return 0;
}