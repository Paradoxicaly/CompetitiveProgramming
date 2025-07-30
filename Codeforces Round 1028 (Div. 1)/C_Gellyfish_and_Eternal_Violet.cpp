/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{"; int f = 0;
    for (auto &x : vec) o << (f++ ? " " : "") << x;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m\n";
}
#define bug_(c, x...) bug__(c, __LINE__, "[" #x "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
constexpr auto min(T... a) { return std::min({a...}); }
template<class... T>
constexpr auto max(T... a) { return std::max({a...}); }

template<class... T>
void input(T&... a) { (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll power(ll a, ll b, ll mod = (ll)1e9+7) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

void solve() {
    int n, m, p1;
    input(n, m, p1);
    double p = p1 / 100.0;
    vi h(n);
    rep(i, n) { input(h[i]); --h[i]; }

    int minh = *min_element(all(h));
    int sum = 0;
    rep(i, n) sum += h[i] - minh;

    vector<double> dp1(sum + 1), dp2(n * minh + 1), dp3(minh + 1);
    dp1[0] = 1.0;
    dp2[0] = 1.0;

    rng(i, 1, m + 1) {
        vector<double> ndp1(sum + 1), ndp2(n * minh + 1), ndp3(minh + 1);
        rep(x, sum + 1) {
            if (x == 0) ndp1[x] = 1.0;
            else ndp1[x] = p * dp1[x] + (1 - p) * dp1[x - 1];
        }
        rep(x, n * minh + 1) {
            if (x == 0) ndp2[x] = 1.0;
            else if (x < n)
                ndp2[x] = p * dp2[x] + (1 - p) * max(dp2[x], dp2[x - 1]);
            else
                ndp2[x] = p * max(dp2[x], dp2[x - n]) + (1 - p) * max(dp2[x], dp2[x - 1]);
        }
        rep(x, min(minh, m - i) + 1) {
            int a = minh - x;
            int b = sum - (m - i - x);
            if (a <= 0 || b <= 0) continue;
            ndp3[x] += p * (a == 1 ? dp1[b] : dp3[x + 1]);
            ndp3[x] += (1 - p) * (b == 1 ? dp2[a * n] : dp3[x]);
        }
        dp1 = move(ndp1);
        dp2 = move(ndp2);
        dp3 = move(ndp3);
    }

    double ans;
    if (minh == 0) ans = dp1[sum];
    else if (sum == 0) ans = dp2[n * minh];
    else ans = dp3[0];

    cout << fixed << setprecision(6) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}