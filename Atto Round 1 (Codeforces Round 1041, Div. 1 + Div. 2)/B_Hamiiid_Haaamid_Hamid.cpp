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
    int n, x;
    string s;
    input(n, x);
    input(s);
    int L = 0;      
    int R = n + 1;   
    
    for (int i = x - 2; i >= 0; --i) {
        if (s[i] == '#') { L = i + 1; break; } 
    }
    for (int i = x; i < n; ++i) {
        if (s[i] == '#') { R = i + 1; break; } 
    }

    int a = min(x, n - R + 2);      
    int b = min(L + 1, n - x + 1);  
    int ans = max(a, b);
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
