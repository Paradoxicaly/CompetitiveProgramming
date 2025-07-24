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

void solve() {
    int n;
    cin >> n;
    
    vector<int> b(2 * n);
    rep(i, 2 * n) {
        cin >> b[i];
    }
    
    sort(all(b));
    
    vector<ll> a(2 * n + 1);
    ll res = 0;
    rep(i, n - 1) {
        a[2 * i + 1] = b[i];
        res -= b[i];
    }
    rep(i, n + 1) {
        a[2 * i] = b[n - 1 + i];
        res += b[n - 1 + i];
    }
    a[2 * n - 1] = res;
    
    rep(i, 2 * n + 1) {
        cout << a[i] << " \n"[i == 2 * n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}