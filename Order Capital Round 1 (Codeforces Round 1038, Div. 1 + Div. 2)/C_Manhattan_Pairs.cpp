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
 
struct T {
    int x, y, id;
};
 
void solve() {
    int n;
    cin >> n;
    vector<T> v(n);
    rep(i, n) {
        cin >> v[i].x >> v[i].y;
        v[i].id = i + 1;
    }
 
    sort(all(v), [](const T& a, const T& b) {
        return a.x < b.x;
    });
 
    int k = n / 2;
    vector<T> L(v.begin(), v.begin() + k);
    vector<T> R(v.begin() + k, v.end());
 
    sort(all(L), [](const T& a, const T& b) {
        return a.y < b.y;
    });
    sort(all(R), [](const T& a, const T& b) {
        return a.y < b.y;
    });
 
    rep(i, k) {
        cout << L[i].id << " " << R[k - 1 - i].id << '\n';
    }
}
 
int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}