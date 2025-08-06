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
const int MAXN = 510;

int f[MAXN][MAXN], c[MAXN][MAXN], lft[MAXN];
char ss[MAXN];

int M(int i, int j) {
    if (ss[i] == '0') return (j + 1) / 2;
    else             return j / 2;
}

void init_combinations() {
    rep(i, MAXN) {
        c[i][0] = 1;
        rng(j, 1, i+1) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
        }
    }
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

void solve() {
    int n, k;
    input(n, k);
    rng(i, 1, n+1) input(ss[i]);
    rep(i, n+2) {
        lft[i] = 0;
        rep(j, k+1) f[i][j] = 0;
        f[i][0] = 1;
    }

    for (int i = n; i >= 1; --i) {
        if (ss[i] == '0') lft[i] = min(k, lft[i+1]*2 + 1);
        else             lft[i] = min(k, lft[i+1]*2);
    }

    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= lft[i]; ++j) {
            ll ways = 0;
            int m = M(i, j);
            for (int t = max(0, j - lft[i+1]); t <= m; ++t) {
                ways = (ways + (ll)f[i+1][j-t] * c[m][t]) % MOD;
            }
            f[i][j] = ways;
        }
    }

    print(f[1][k]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_combinations();
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
