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

int inv(int x, int mod = MOD) {
    return fpow(x, mod - 2, mod);
}

const int MAXN = 1e6 + 5;
int po2[MAXN];
int inv4;

int getans(int u, int v) {
    if (u + v <= 1) return 0;
    int ans = -1LL * po2[u + v - 1] * inv4 % MOD; ans %= MOD;
    int pro = ((u + v) * 1LL * po2[u + v - 1] - v * 1LL * po2[u + v]) % MOD;
    int pro2 = ((((u + v) * 1LL * (u + v - 1)) % MOD) * po2[u + v - 2] - ((v * 1LL * (u + v)) % MOD) * po2[u + v - 1] - ((v * 1LL * (u + v)) % MOD) * po2[u + v - 1] + ((v * 1LL * (v + 1)) % MOD) * po2[u + v]) % MOD;
    ans += (1LL * (pro + pro2) * inv4) % MOD; ans %= MOD;
    return (ans % MOD + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    po2[0] = 1;
    rng(i, 1, MAXN) {
        po2[i] = (1LL * po2[i - 1] * 2) % MOD;
    }
    inv4 = inv(4);

    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        int u = count(all(s), '1');
        int v = count(all(s), '0');
        
        rep(i, q) {
            int pos;
            cin >> pos;
            --pos;
            if (s[pos] == '1') {
                --u; ++v;
            } else {
                --v; ++u;
            }
            s[pos] = '0' + '1' - s[pos];
            cout << getans(u, v) << '\n';
        }
    }
    return 0;
}