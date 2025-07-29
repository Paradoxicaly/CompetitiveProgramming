/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)

const int MOD = 1e9 + 7;

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{";
    int f = 0;
    for (T v : vec) o << (f++ ? " " : "") << v;
    return o << "}";
}
void bug__(int c, auto ...args) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << args << " "));
    cerr << "\e[0m\n";
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
void input(T&... v){ (cin >> ... >> v); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

void solve(){
    ll p, s;
    input(p, s);

    bool foundRect = false;
    ll bestX = -1, bestY = -1;
    for (ll x = 1; x * x <= 50000 && !foundRect; ++x) {
        ll denom = p*x - 2*s;
        if (denom <= 0) continue;
        ll num = 2*s*x;
        if (num % denom != 0) continue;
        ll y = num / denom;
        if (y <= 0) continue;
        if (x*y > 50000) continue;
        bestX = x;
        bestY = y;
        foundRect = true;
    }

    if (foundRect) {
        ll k = bestX * bestY;
        print(k);
        rep(i, bestX) rep(j, bestY) print(i, j);
        return;
    }
    ll n = 2*s;
    ll E = 4*s - p;
    if (E < n-1 || E > 2*n) {
        print(-1);
        return;
    }
    ll K = E - (n-1);  
    if (K < 0 || K > n) {
        print(-1);
        return;
    }
    ll total = n + K;
    if (total > 50000) {
        print(-1);
        return;
    }
    print(total);
    rep(i, n) {
        print(i, 0);
    }
    rep(i, K) {
        int y = (i % 2 == 0 ? 1 : -1);
        print(i, y);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}