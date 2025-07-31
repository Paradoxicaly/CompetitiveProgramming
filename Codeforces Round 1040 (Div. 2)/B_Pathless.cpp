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
    int n, s;
    input(n, s);
    vi a(n);
    rep(i, n) input(a[i]);
    int c0 = 0, c1 = 0, c2 = 0;
    for (int x : a) {
        if (x == 0) ++c0;
        else if (x == 1) ++c1;
        else ++c2;
    }
    int S = c1 + 2*c2;
    if (s < S) {
        sort(all(a));
        rep(i, n) {
            cout << a[i] << (i+1==n? '\n' : ' ');
        }
    } else if (s == S+1) {
        bool fst = true;
        rep(i, c0) {
            if (!fst) cout << ' ';
            cout << 0; fst = false;
        }
        rep(i, c2) {
            if (!fst) cout << ' ';
            cout << 2; fst = false;
        }
        rep(i, c1) {
            if (!fst) cout << ' ';
            cout << 1; fst = false;
        }
        cout << "\n";
    } else {
        cout << "-1\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}