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
    int P, S;
    input(P, S);

    if (P == 2 * S) {
        print(4);
        print(0, 0);
        print(0, 1);
        print(1, 0);
        print(1, 1);
        return;
    }

    for (int x = 1; x * x <= 50000; ++x) {
        for (int y = x; x * y <= 50000; ++y) {
            int per = 2 * (x + y);
            int area = x * y;
            if (1LL * per * S == 1LL * P * area) {
                print(area);
                rep(i, x) rep(j, y) print(i, j);
                return;
            }
            if (y > 1) {
                ll d = 1LL * S * (per + 2) - 1LL * area * P;
                if (d % P == 0) {
                    d /= P;
                    if (d >= 1 && d < y && area + d <= 50000) {
                        print(area + d);
                        rep(i, x) rep(j, y) print(i, j);
                        rep(i, (int)d) print(x, i);
                        return;
                    }
                }
            }
        }
    }
    print(-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    input(T);
    while (T--) solve();
    return 0;
}