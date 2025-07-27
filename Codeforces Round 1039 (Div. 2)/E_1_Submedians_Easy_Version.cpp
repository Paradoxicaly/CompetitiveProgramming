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
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a; (cout << ... << (cout << ' ', b)); cout << '\n';
}

void solve() {
    int n, k;
    input(n, k);
    vi a(n);
    rep(i, n) input(a[i]);
    int low = 1, high = n, ans = 1;
    int bestL = 1, bestR = k;
    while (low <= high) {
        int mid = (low + high) / 2;
        vector<int> pref(n + 1);
        rep(i, n) pref[i+1] = pref[i] + (a[i] >= mid ? 1 : -1);
        int minpref = 0, minpos = 0;
        bool ok = false;
        for (int i = k; i <= n; ++i) {
            if (pref[i-k] < minpref) {
                minpref = pref[i-k];
                minpos = i-k;
            }
            if (pref[i] - minpref >= 0) {
                ok = true;
                bestL = minpos + 1;
                bestR = i;
                break;
            }
        }
        if (ok) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    print(ans, bestL, bestR);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while (T--) solve();
    return 0;
}