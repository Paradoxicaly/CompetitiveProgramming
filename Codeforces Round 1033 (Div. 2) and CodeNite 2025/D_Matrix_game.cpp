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

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
int inv[N];

void precompute() {
    inv[1] = 1;
    rng(i, 2, N) {
        inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    ll x = 1LL * (a - 1) * k + 1;
    int xm = x % MOD;

    int c = 1;
    rep(i, a) {
        c = 1LL * c * (xm - i) % MOD * inv[i + 1] % MOD;
    }
    c = (1LL * c * (b - 1) % MOD * k % MOD + 1) % MOD;
    if (c < 0) c += MOD;
    cout << xm << ' ' << c << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}