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

const int MOD = 998244353;
const int N = 110;
const int LOGN = 10;

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

ll fac[N], inv[N];
ll dp[N][N][LOGN][LOGN];
int n;
ll s[N];

void init_C() {
    fac[0] = 1;
    rng(i, 1, N) fac[i] = (fac[i-1] * i) % MOD;
    inv[N-1] = power(fac[N-1], MOD-2);
    for (int i = N-2; i >= 0; i--) inv[i] = (inv[i+1] * (i+1)) % MOD;
}

ll C(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    return fac[n] * inv[m] % MOD * inv[n-m] % MOD;
}

void solve() {
    input(n);
    rng(i, 1, n+1) input(s[i]);
    
    rep(i, N) rep(j, N) rep(ii, LOGN) rep(jj, LOGN) dp[i][j][ii][jj] = 0;
    
    dp[1][1][0][1] = (s[1] < 1);
    rng(i, 2, n+1) dp[i][i][1][0] = (s[i] < 1);
    rng(i, 1, n+1) dp[i][i-1][0][0] = dp[i+1][i][0][0] = 1;
    
    rng(len, 2, n+1) {
        rng(l, 1, n-len+2) {
            int r = l + len - 1;
            if (r > n) break;
            
            rep(ii, min(LOGN, len+1)) {
                rep(jj, min(LOGN, len+1)) {
                    rng(k, l, r+1) {
                        int tagl = 0, tagr = 0;
                        if (l == 1 && r == n) tagl = tagr = 0;
                        else if (l == 1) tagr = 1;
                        else if (r == n) tagl = 1;
                        else {
                            if (abs(l-1-k) <= abs(k-(r+1))) tagl = 1;
                            else tagr = 1;
                        }
                        
                        if (ii < tagl || jj < tagr) continue;
                        
                        if (s[k] == -1) {
                            ll suml = 0, sumr = 0;
                            rep(kk, LOGN) {
                                suml = (suml + dp[l][k-1][ii-tagl][kk]) % MOD;
                                sumr = (sumr + dp[k+1][r][kk][jj-tagr]) % MOD;
                            }
                            if (suml && sumr) {
                                dp[l][r][ii][jj] = (dp[l][r][ii][jj] + suml * sumr % MOD * C(r-l, k-l)) % MOD;
                            }
                        } else {
                            rep(kk, LOGN) {
                                int val = s[k] - kk;
                                if (val < 0 || val >= LOGN) continue;
                                ll left_val = dp[l][k-1][ii-tagl][kk];
                                ll right_val = dp[k+1][r][val][jj-tagr];
                                if (left_val && right_val) {
                                    dp[l][r][ii][jj] = (dp[l][r][ii][jj] + left_val * right_val % MOD * C(r-l, k-l)) % MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    print(dp[1][n][0][0]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    init_C();
    
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}