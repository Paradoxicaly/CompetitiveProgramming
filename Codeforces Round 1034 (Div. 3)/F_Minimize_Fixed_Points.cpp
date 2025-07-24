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

const int MX = 1000001;
int gpf[MX];

void solve() {
    int N;
    input(N);
    map<int, vector<int>> leastFacs;
    rng(i, 2, N + 1) {
        leastFacs[gpf[i]].pb(i);
    }
    vector<int> ans(N);
    ans[0] = 1;
    for (auto& a : leastFacs) {
        vector<int>& cur = a.se;
        rep(i, sz(cur)) {
            ans[cur[i] - 1] = cur[(i + 1) % sz(cur)];
        }
    }
    rep(i, N) {
        cout << ans[i] << " ";
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    rng(i, 2, MX) {
        if (gpf[i] == 0) {
            for (int j = i; j < MX; j += i) {
                gpf[j] = i;
            }
        }
    }
    int T = 1;
    input(T);
    while (T--) {
        solve();
    }

    return 0;
}