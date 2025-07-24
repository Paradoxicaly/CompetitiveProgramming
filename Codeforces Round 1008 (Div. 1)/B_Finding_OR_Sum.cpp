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
    int even = 0, odd = 0;
    rep(i, 30) {
        if (i % 2 == 0) {
            even |= 1 << i;
        } else {
            odd |= 1 << i;
        }
    }
    
    int a[2];
    cout << even << endl;
    cin >> a[0];
    cout << odd << endl;
    cin >> a[1];
    
    a[0] -= even * 2;
    a[1] -= odd * 2;
    swap(a[0], a[1]);
    
    int cnt[30] {};
    rep(i, 30) {
        if (a[i % 2] >> i & 1) {
            cnt[i] = 1;
        } else if (a[i % 2] >> (i + 1) & 1) {
            cnt[i] = 2;
        }
    }
    
    cout << "!" << endl;
    
    int m;
    cin >> m;
    
    int ans = 0;
    rep(i, 30) {
        if (m >> i & 1) {
            ans += 2 << i;
        } else {
            ans += cnt[i] << i;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}