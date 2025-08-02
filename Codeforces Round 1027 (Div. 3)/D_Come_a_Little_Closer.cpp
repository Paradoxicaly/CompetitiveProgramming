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

void solve() {
    int n;
    input(n);
    vector<pair<ll,ll>> pts(n);
    rep(i,n) input(pts[i].first, pts[i].second);

    if (n == 1) {
        print(1);
        return;
    }

    ll xmin1 = LLONG_MAX, xmin2 = LLONG_MAX;
    ll xmax1 = LLONG_MIN, xmax2 = LLONG_MIN;
    int cnt_xmin1 = 0, cnt_xmax1 = 0;
    ll ymin1 = LLONG_MAX, ymin2 = LLONG_MAX;
    ll ymax1 = LLONG_MIN, ymax2 = LLONG_MIN;
    int cnt_ymin1 = 0, cnt_ymax1 = 0;

    for (auto &p : pts) {
        ll x = p.first, y = p.second;
        if (x < xmin1) { xmin2 = xmin1; xmin1 = x; cnt_xmin1 = 1; }
        else if (x == xmin1) { cnt_xmin1++; }
        else if (x < xmin2) { xmin2 = x; }
        if (x > xmax1) { xmax2 = xmax1; xmax1 = x; cnt_xmax1 = 1; }
        else if (x == xmax1) { cnt_xmax1++; }
        else if (x > xmax2) { xmax2 = x; }

        if (y < ymin1) { ymin2 = ymin1; ymin1 = y; cnt_ymin1 = 1; }
        else if (y == ymin1) { cnt_ymin1++; }
        else if (y < ymin2) { ymin2 = y; }
        if (y > ymax1) { ymax2 = ymax1; ymax1 = y; cnt_ymax1 = 1; }
        else if (y == ymax1) { cnt_ymax1++; }
        else if (y > ymax2) { ymax2 = y; }
    }

    ll ans = LLONG_MAX;
    rep(i,n) {
        ll x = pts[i].first, y = pts[i].second;
        ll mnx = xmin1, mxx = xmax1;
        ll mny = ymin1, mxy = ymax1;
        if (x == xmin1 && cnt_xmin1 == 1) mnx = xmin2;
        if (x == xmax1 && cnt_xmax1 == 1) mxx = xmax2;
        if (y == ymin1 && cnt_ymin1 == 1) mny = ymin2;
        if (y == ymax1 && cnt_ymax1 == 1) mxy = ymax2;

        ll w = mxx - mnx + 1;
        ll h = mxy - mny + 1;
        ll area_box = w * h;

        ll cost;
        if (area_box >= n) {
            cost = area_box;
        } else {
            cost = min( (w + 1) * h,
                        w * (h + 1) );
        }
        ans = min(ans, cost);
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