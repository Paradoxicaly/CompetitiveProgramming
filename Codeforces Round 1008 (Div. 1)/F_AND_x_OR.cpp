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

template<class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool chmax(T &a, const T &b) {
    if (b > a) {
        a = b;
        return true;
    }
    return false;
}

const int INF = 2e9;
const ll INFLL = 2e18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    ll ans = 0;
    rep(i, n) ans += abs(a[i] - b[i]);

    sort(all(b));
    if (unique(all(b)) != b.end()) {
        cout << "0\n";
        return;
    }

    if (n == 1) {
        cout << ans << '\n';
        return;
    }

    int v = 0;
    while ((1 << v) <= m) v++;

    vector<int> dp(1 << v, INF);

    rep(i, n - 1) ans = min(ans, 1LL * b[i + 1] - b[i]);

    b.pb(1 << v);

    for (int i = n - 1; i >= 0; --i) {
        int l = b[i];
        int r = b[i + 1];

        for (int mask = r - 1; mask >= l; --mask) {
            rep(bit, v) {
                if (mask & (1 << bit)) continue;
                int up = dp[mask ^ (1 << bit)];
                ans = min(ans, 1LL * up + mask - l);
                chmin(dp[mask], up);
            }
        }
        for (int mask = r - 1; mask >= l; --mask) {
            chmin(dp[mask], mask - l);
        }
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