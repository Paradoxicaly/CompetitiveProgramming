/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define fi first
#define se second
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

template<class T> bool chmin(T& a, T b) { return (b < a ? a = b, true : false); }
template<class T> bool chmax(T& a, T b) { return (b > a ? a = b, true : false); }

int n, k;
struct node {
    int l, r, x;
} a[200005];

bool cmp(const node& a, const node& b) {
    return a.x < b.x;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].x;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        if (a[i].l <= k && k <= a[i].r && a[i].x > k) {
            k = a[i].x;
        }
    }
    cout << k << '\n';
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}