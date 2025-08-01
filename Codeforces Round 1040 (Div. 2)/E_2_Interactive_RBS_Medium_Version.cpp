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

const int MOD = 1e9 + 7;

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

template<class... T>
constexpr auto min(T... a){
    return std::min({a...});
}

template<class... T>
constexpr auto max(T... a){
    return std::max({a...});
}

template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll query(const vi& idxs) {
    cout << "? " << sz(idxs);
    for (int i : idxs) cout << " " << i + 1;
    cout << endl;
    ll res;
    cin >> res;
    if (res == -1) exit(0);
    return res;
}

ll range_query(int l, int r) {
    if (l > r) return 0;
    vi idxs;
    for (int i = l; i <= r; ++i) idxs.pb(i);
    return query(idxs);
}

void solve() {
    int n;
    input(n);

    vi w0 = {1, 2, 3, 5, 7, 10, 15, 21, 30, 43, 61, 87, 123};
    int m = sz(w0);
    vector<ll> w1(m);
    rep(i, m) w1[i] = 1LL * w0[i] * (w0[i] + 1) / 2;

    string s(n, '?');
    int im = -1;
    ll fs = range_query(0, n - 1);
    if (fs == 0) {
        im = 0;
    } else {
        function<pii(int, int)> find_pos = [&](int l, int r) -> pii {
            if (l + 1 == r) return {l, r};
            int mid = (l + r) / 2;
            if (range_query(l, mid) > 0) return find_pos(l, mid);
            if (range_query(mid + 1, r) > 0) return find_pos(mid + 1, r);
            return {mid, mid + 1};
        };
        im = find_pos(0, n - 1).se;
    }

    vi idxs(n); iota(all(idxs), 0);
    for (int i = 0; i < n; i += m) {
        int bsize = min(m, n - i);
        vi bidxs;
        rep(j, bsize) bidxs.pb(idxs[i + j]);

        vi qidxs;
        rep(j, bsize) {
            int idx = bidxs[j];
            rep(k, w0[j]) {
                qidxs.pb(idx);
                qidxs.pb(im);
            }
            qidxs.pb(im);
        }

        ll f = query(qidxs);
        for (int j = bsize - 1; j >= 0; --j) {
            int idx = bidxs[j];
            if (f >= w1[j]) {
                s[idx] = '(';
                f -= w1[j];
            } else {
                s[idx] = ')';
            }
        }
    }

    cout << "! " << s << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while (T--) solve();
    return 0;
}
