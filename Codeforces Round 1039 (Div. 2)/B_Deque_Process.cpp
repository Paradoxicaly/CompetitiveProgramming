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
    int n;
    input(n);
    vector<int> a(n);
    rep(i,n) input(a[i]);
    int l = 0, r = n - 1;
    string ans;
    ans.reserve(n);
    rep(i,n) {
        if ((i % 2 == 0 && a[l] < a[r]) || (i % 2 == 1 && a[l] >= a[r])) {
            ans.pb('L');
            ++l;
        } else {
            ans.pb('R');
            --r;
        }
    }
    print(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while (T--) solve();
    return 0;
}