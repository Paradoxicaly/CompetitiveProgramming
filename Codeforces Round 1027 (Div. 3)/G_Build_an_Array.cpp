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
    o << "{";
    int f = 0;
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
void print() { cout << '\n'; }

void solve() {
    int n, k;
    input(n, k);
    vector<int> a(n);
    rep(i, n) input(a[i]);
    auto max_op = [&](int A, int B) {
        ll min_part = A;
        while (min_part % 2 == 0 && min_part / 2 != B) {
            min_part /= 2;
        }
        if (min_part % 2 == 1) {
            return (ll)(A / min_part);
        }
        ll true_min = min_part;
        while (true_min % 2 == 0) {
            true_min /= 2;
        }
        return 1LL + (A - min_part) / true_min;
    };

    vector<ll> pre(n, 0), suf(n, 0);
    rng(j, 1, n) {
        pre[j] = pre[j - 1] + max_op(a[j - 1], a[j]);
    }
    for (int j = n - 2; j >= 0; --j) {
        suf[j] = suf[j + 1] + max_op(a[j + 1], a[j]);
    }
    rep(i, n) {
        ll ops = max_op(a[i], 0) + pre[i] + suf[i];
        if (ops >= k) {
            print("YES");
            return;
        }
    }
    print("NO");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
