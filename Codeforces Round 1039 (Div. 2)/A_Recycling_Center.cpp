/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i,n) for (int i = 0; i < (n); ++i)

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a; (cout << ... << (cout << ' ', b)); cout << '\n';
}

void solve() {
    int n; ll c;
    input(n, c);
    vector<ll> a(n);
    rep(i, n) input(a[i]);
    vector<int> deadlines;
    for (ll w : a) {
        if (w > c) continue;
        ll q = c / w;
        int k = 63 - __builtin_clzll(q);
        deadlines.push_back(k + 1);
    }
    sort(deadlines.begin(), deadlines.end());
    int time = 1, free_count = 0;
    for (int d : deadlines) {
        if (d >= time) {
            free_count++;
            time++;
        }
    }
    print(n - free_count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}