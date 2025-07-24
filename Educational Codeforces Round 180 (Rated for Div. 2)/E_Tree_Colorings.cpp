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

const int MOD = 998244353;

int fpow(int base, int exp, int mod = MOD) {
    int res = 1;
    for (base %= mod; exp > 0; exp >>= 1) {
        if (exp & 1) res = (1LL * res * base) % mod;
        base = (1LL * base * base) % mod;
    }
    return res;
}

const int MAXN = 510000;
int f[MAXN], g[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(g, 0x3f, sizeof(g));
    g[1] = 0;
    f[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        f[i] = g[i - 2] + 1;
        for (int j = 1; i * j < MAXN; ++j) {
            g[i * j] = min(g[i * j], g[j] + f[i]);
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (g[n] > 1000000000) {
            cout << "-1\n";
        } else {
            cout << g[n] + 1 << '\n';
        }
    }
    return 0;
}