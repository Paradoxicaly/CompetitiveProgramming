/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(x) begin(x), end(x)
#define rep(i,n) for (int i = 0; i < (n); ++i)

template<class... T>
void input(T&... a) { (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}

void solve() {
    int n, k;
    input(n, k);
    vector<ll> a(n), b(n);
    rep(i, n) input(a[i]);
    rep(i, n) input(b[i]);
    vector<pair<ll,ll>> seg(n);
    ll initial_sum = 0;
    rep(i, n) {
        ll x = min(a[i], b[i]);
        ll y = max(a[i], b[i]);
        seg[i] = {x, y};
        initial_sum += (y - x);
    }
    sort(all(seg));
    ll max_y = seg[0].second;
    ll minimal_gap = LLONG_MAX;
    for (int i = 1; i < n; ++i) {
        ll x = seg[i].first, y = seg[i].second;
        if (x <= max_y) {
            minimal_gap = 0;
            break;
        }
        minimal_gap = min(minimal_gap, x - max_y);
        max_y = max(max_y, y);
    }
    ll answer = initial_sum + 2LL * minimal_gap;
    print(answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    input(T);
    while (T--) solve();
    return 0;
}
