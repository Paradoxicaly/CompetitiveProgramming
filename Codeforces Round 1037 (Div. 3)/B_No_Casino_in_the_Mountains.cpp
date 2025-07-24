/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fi first
#define se second
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define lowbit(x) ((x) & (-(x)))

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

template<class T> bool chmin(T& a, T b) { return (b < a ? a = b, true : false); }
template<class T> bool chmax(T& a, T b) { return (b > a ? a = b, true : false); }

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 5), b(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = b[i - 1] + a[i];
    }

    int now = 1, ans = 0;
    while (1) {
        if (now + k - 1 > n) break;
        if (b[now + k - 1] == b[now - 1]) {
            now = now + k + 1;
            ans++;
        } else {
            now++;
        }
    }

    cout << ans << "\n";
}

int main() {
    cincout();
    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}