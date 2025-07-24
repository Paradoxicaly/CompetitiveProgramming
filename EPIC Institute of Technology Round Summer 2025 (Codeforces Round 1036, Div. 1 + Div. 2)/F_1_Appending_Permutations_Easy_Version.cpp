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
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif

template <typename T> T mod_inv_in_range(T a, T m) {
    T x = a, y = m;
    T vx = 1, vy = 0;
    while (x) {
        T k = y / x;
        y %= x;
        vy -= k * vx;
        swap(x, y);
        swap(vx, vy);
    }
    assert(y == 1);
    return vy < 0 ? m + vy : vy;
}

template <int MOD_>
struct modnum {
    static constexpr int MOD = MOD_;
    int v;
    modnum() : v(0) {}
    modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }

    explicit operator int() const { return v; }
    friend ostream& operator<<(ostream &o, const modnum &n) { return o << int(n); }
    friend istream& operator>>(istream &i, modnum &n) { ll v_; i >> v_; n = modnum(v_); return i; }

    modnum inv() const { return mod_inv_in_range(v, MOD); }

    modnum neg() const { return v == 0 ? 0 : MOD - v; }

    modnum& operator+=(const modnum &o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    modnum& operator-=(const modnum &o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    modnum& operator*=(const modnum &o) { v = int((ll)v * o.v % MOD); return *this; }
    modnum& operator/=(const modnum &o) { return *this *= o.inv(); }

    friend modnum operator+(modnum a, const modnum &b) { return a += b; }
    friend modnum operator-(modnum a, const modnum &b) { return a -= b; }
    friend modnum operator*(modnum a, const modnum &b) { return a *= b; }
    friend modnum operator/(modnum a, const modnum &b) { return a /= b; }
};

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> bads(2 * N - 1);
    rep(e, M) {
        int i, x;
        cin >> i >> x;
        i--, x--;
        bads[i - x + (N - 1)].pb(i);
    }

    for (auto &v : bads) sort(all(v), greater<>());

    using num = modnum<998244353>;
    vector<num> dp(N + 1);
    dp[0] = 1;

    rep(i, N) {
        int off = i + (N - 1);
        int jmax = N;
        if (!bads[off].empty()) jmax = bads[off].back();

        rng(j, i + 2, jmax + 1) {
            int kmax = min(N, 2 * j - i - 1);
            int bj = j + (N - 1);
            if (j < N && !bads[bj].empty()) {
                kmax = min(kmax, bads[bj].back());
            }
            rng(k, j + 1, kmax + 1) {
                dp[k] -= dp[i];
            }
        }

        rng(off2, i, i + N) {
            int x0 = i + (N - 1) - off2;
            auto &b = bads[off2];
            while (!b.empty() && b.back() < i) b.pop_back();
            int jmax2 = N - x0;
            if (!b.empty()) jmax2 = min(jmax2, b.back());

            rng(j, i + 1, jmax2 + 1) {
                if (j == N || bads[j + (N - 1)].empty() || bads[j + (N - 1)].back() >= j + x0) {
                    dp[j + x0] += dp[i];
                }
            }
        }
    }

    cout << dp[N] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}