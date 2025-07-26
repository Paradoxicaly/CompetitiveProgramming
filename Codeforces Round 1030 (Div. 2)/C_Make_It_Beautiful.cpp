#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)

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

static auto popc = [](ull x){ return (ll)__builtin_popcountll(x); };
static auto trail = [](ull x){ return __builtin_ctzll(~x); };
static auto nxtcost = [&](ull x){ return (x & 1ULL) ? (1ULL << trail(x)) : 1ULL; };

void solve() {
    int n; ull k;
    input(n, k);
    vector<ull> a(n);
    rep(i, n) input(a[i]);
    ll ans = 0;
    rep(i, n) ans += popc(a[i]);
    priority_queue<pair<ull,int>, vector<pair<ull,int>>, greater<>> pq;
    rep(i, n) pq.push({ nxtcost(a[i]), i });
    while (!pq.empty() && pq.top().first <= k) {
        auto [c, i] = pq.top(); pq.pop();
        k -= c;
        ans += 1;
        a[i] += c;
        ull nc = nxtcost(a[i]);
        if (nc <= k) pq.push({nc, i});
    }
    print(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}