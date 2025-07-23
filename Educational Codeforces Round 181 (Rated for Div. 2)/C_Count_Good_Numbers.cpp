/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define fi first
#define se second

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define pb push_back

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MOD = 998244353;
ll modpow(ll a, ll b, ll m = MOD) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}
ll modinv(ll a, ll m = MOD) {
    return modpow(a, m - 2, m);
}

const int MAX = 200005;
ll fact[MAX], ifact[MAX];
void init_factorials() {
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fact[i] = fact[i-1] * i % MOD;
        ifact[i] = modinv(fact[i]);
    }
}
ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

template<class T> bool chmin(T& a, T b) { return (b < a ? a = b, true : false); }
template<class T> bool chmax(T& a, T b) { return (b > a ? a = b, true : false); }

ll cnt(ll x) {
    ll res = 0;
    int p[4] = {2, 3, 5, 7};
    for (int m = 0; m < 16; m++) {
        ll pr = 1;
        int c = 0;
        for (int i = 0; i < 4; i++) {
            if (m >> i & 1) {
                pr *= p[i];
                c++;
            }
        }
        if (pr > x) continue;
        ll t = x / pr;
        res += (c % 2 == 0 ? t : -t);
    }
    return res;
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) {
        ll l, r;
        cin >> l >> r;
        cout << cnt(r) - cnt(l - 1) << '\n';
    }
    return 0;
}