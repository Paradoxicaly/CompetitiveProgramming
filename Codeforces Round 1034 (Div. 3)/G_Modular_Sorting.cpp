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

template<class T, class U>
T gcd(T a, U b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

const int MAXN = 500001;
vector<vector<int>> factor;

void init(int n) {
    factor.assign(n + 1, {});
    rng(i, 1, n + 1) {
        for (int j = i; j <= n; j += i) {
            factor[j].pb(i);
        }
    }
}

void solve() {
    int n, m, q;
    input(n, m, q);
    vector<int> a(n);
    rep(i, n) input(a[i]);

    map<int, int> cnt;
    rep(i, n - 1) {
        for (auto & d : factor[m]) {
            if (a[i] % d > a[i + 1] % d) {
                cnt[d] += 1;
            }
        }
    }

    while (q--) {
        int op;
        input(op);
        if (op == 1) {
            int p, x;
            input(p, x);
            --p;
            if (p) {
                for (auto & d : factor[m]) {
                    if (a[p - 1] % d > a[p] % d) {
                        cnt[d] -= 1;
                    }

                    if (a[p - 1] % d > x % d) {
                        cnt[d] += 1;
                    }
                }
            }

            if (p + 1 < n) {
                for (auto & d : factor[m]) {
                    if (a[p] % d > a[p + 1] % d) {
                        cnt[d] -= 1;
                    }

                    if (x % d > a[p + 1] % d) {
                        cnt[d] += 1;
                    }
                }
            }
            a[p] = x;
        } else {
            int k;
            input(k);
            int d = ::gcd(k, m);
            if (cnt[d] <= (m / d - 1)) {
                print("YES");
            } else {
                print("NO");
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    init(5e5);
    input(t);
    while (t--) {
        solve();
    }
    return 0;
}