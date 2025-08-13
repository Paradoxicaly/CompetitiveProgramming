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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    input(T);
    struct Q { ll x, y; int k; };
    vector<Q> qs(T);
    int maxk = 1;
    rep(i, T) {
        input(qs[i].x, qs[i].y, qs[i].k);
        maxk = max(maxk, qs[i].k);
    }

    int MX = maxk + 1;
    vector<vector<int>> byk(MX);
    rep(i, T) {
        byk[qs[i].k].pb(i);
    }

    const int INF = 1e9;
    vector<int> dp(MX, INF);
    dp[1] = 0;

    vector<int> ans(T, -1);
    for (int k = 1; k < MX; ++k) {
        for (int v = 1; v * k < MX; ++v) {
            dp[v * k] = min(dp[v * k], dp[v] + 1);
        }
        for (int idx : byk[k]) {
            ll x = qs[idx].x, y = qs[idx].y;
            ll g = gcd(x, y);
            ll need_div = x / g;
            ll need_mul = y / g;
            if (need_div < MX && need_mul < MX
                && dp[need_div] < INF
                && dp[need_mul] < INF) {
                ans[idx] = dp[need_div] + dp[need_mul];
            } else {
                ans[idx] = -1;
            }
        }
    }

    rep(i, T) {
        print(ans[i]);
    }
    return 0;
}