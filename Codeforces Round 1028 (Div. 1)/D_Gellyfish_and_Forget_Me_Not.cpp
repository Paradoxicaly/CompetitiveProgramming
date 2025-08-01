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
    for (auto &x : vec) o << (f++ ? " " : "") << x;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m\n";
}
#define bug(x...) bug__(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
void input(T&... a) { (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    input(n);
    vector<ll> a(n), b(n);
    rep(i, n) input(a[i]);
    rep(i, n) input(b[i]);
    string c;
    input(c);

    vector<ll> v(60);
    vector<int> val(60, -1);
    ll x = 0;

    for (int i = n - 1; i >= 0; --i) {
        x ^= a[i];
        ll d = a[i] ^ b[i];
        for (int j = 59; j >= 0; --j) {
            if ((d >> j) & 1) {
                if (val[j] == -1) {
                    val[j] = c[i] - '0';
                    v[j] = d;
                    break;
                } else {
                    d ^= v[j];
                }
            }
        }
    }

    for (int j = 59; j >= 0; --j) {
        if (val[j] == 0 && ((x >> j) & 1)) x ^= v[j];
        if (val[j] == 1 && !((x >> j) & 1)) x ^= v[j];
    }

    print(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}