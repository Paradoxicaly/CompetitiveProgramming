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
 
    vector<vector<int>> arr(n, vector<int>(n, -1));
    int x, y;
 
    if (n % 2 == 0) {
        x = n / 2 - 1;
        y = n / 2 - 1;
    } else {
        x = n / 2;
        y = n / 2;
    }
 
    arr[x][y] = 0;
    int value = 1, step = 1;
 
    vector<pair<int, int>> dir = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };
 
    while (value < n * n) {
        for (int d = 0; d < 4; ++d) {
            int steps = step;
            if (d % 2 == 1) ++step;
 
            int dx = dir[d].first;
            int dy = dir[d].second;
 
            for (int i = 0; i < steps; ++i) {
                x += dx;
                y += dy;
 
                if (x >= 0 && x < n && y >= 0 && y < n && arr[x][y] == -1) {
                    arr[x][y] = value++;
                }
 
                if (value >= n * n) break;
            }
 
            if (value >= n * n) break;
        }
    }
 
    for (const auto& row : arr) {
        for (int i = 0; i < n; ++i) {
            cout << row[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    cout << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}