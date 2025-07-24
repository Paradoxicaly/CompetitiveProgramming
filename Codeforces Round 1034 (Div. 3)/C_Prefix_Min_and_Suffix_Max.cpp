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

const int N = 210000;
int n, a[N];

void solve() {
    input(n);
    rng(i, 1, n + 1)
        input(a[i]);
    string s(n, '0');
    int mn = numeric_limits<int>::max();
    rng(i, 1, n + 1) {
        mn = min(mn, a[i]);
        if (a[i] == mn) s[i - 1] = '1';
    }
    int mx = numeric_limits<int>::min();
    for (int i = n; i >= 1; i--) {
        mx = max(mx, a[i]);
        if (a[i] == mx) s[i - 1] = '1';
    }
    print(s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while (T--) solve();
    return 0;
}