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

const int MAXN = 1 << 17;
int H[MAXN];

void solve() {
    int N, K;
    cin >> N >> K;
    rep(i, N) cin >> H[i];
    int h = H[K - 1];
    sort(H, H + N);
    bool out = false;
    rep(i, N) {
        if (H[i] > h) {
            int tm = H[i] - h;
            if (i > 0 && tm > H[i - 1]) out = true;
        }
    }
    cout << (out ? "NO\n" : "YES\n");
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}