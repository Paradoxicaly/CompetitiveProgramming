/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)

const int MOD = 1e9+7;

#define N 500005
static int a[N];
static ll s[N];
const ll inf = (ll)1e18;

template<class... T>
void input(T&... x) { (cin >> ... >> x); }
template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}

void solve() {
    int n, m;
    input(n, m);
    for(int i = 1; i <= m; ++i) input(a[i]);
    sort(a+1, a+m+1);
    s[0] = 0;
    for(int i = 1; i <= m; ++i) {
        s[i] = s[i-1] + (a[i]/100);
    }

    ll best = 0;
    int bestL = 0, bestR = 0;
    for(int i = 0, j = n; i <= n; ++i, --j) {
        ll leftScore  = s[m] - s[m-i] - s[i];
        ll rightScore = s[m] - s[m-j] - s[j];
        if (i==0 && j==n) { 
            best = leftScore + rightScore; 
            bestL = i; 
            bestR = j; 
        }
        else if (leftScore + rightScore > best) {
            best = leftScore + rightScore;
            bestL = i;
            bestR = j;
        }
    }

    int I = bestL, J = bestR;
    for(int t = 1; t <= n; ++t) {
        if (I > 0) {
            int u = a[I];
            int v = a[I + m - bestL];
            cout << u << ' ' << v << ' '
                 << u << ' ' << v << ' '
                 << u << ' ' << v << '\n';
            --I;
        } else {
            int u = a[J + m - bestR];
            int v = a[J];
            cout << u << ' ' << v << ' '
                 << u << ' ' << v << ' '
                 << u << ' ' << v << '\n';
            --J;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}