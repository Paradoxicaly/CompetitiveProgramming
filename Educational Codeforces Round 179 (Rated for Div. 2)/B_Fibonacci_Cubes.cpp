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
    int n, m;
    input(n, m);
    vector<int> f(n+1);
    f[1] = 1;
    f[2] = 2;
    for (int i = 3; i <= n; ++i) {
        f[i] = f[i-1] + f[i-2];
    }
    string ans;
    ans.reserve(m);
    rep(i, m) {
        int w, l, h;
        input(w, l, h);
        if (w < f[n] || l < f[n] || h < f[n]) {
            ans.pb('0');
        } else if (h >= f[n] + f[n-1] || w - f[n] >= f[n-1] || l - f[n] >= f[n-1]) {
            ans.pb('1');
        } else {
            ans.pb('0');
        }
    }
    print(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}