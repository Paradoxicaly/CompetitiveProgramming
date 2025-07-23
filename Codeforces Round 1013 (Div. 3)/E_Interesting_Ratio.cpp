/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fi first
#define se second
#define pb push_back

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rng(i, a, b) for (int i = (a); i < (b); ++i)
#define rrep(i, a, b) for (int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MAXN = 10000000;
bool isPrime[MAXN + 1];
int piArray[MAXN + 1];

void computePi() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
    int cnt = 0;
    rep(x, MAXN + 1) {
        if (isPrime[x]) cnt++;
        piArray[x] = cnt;
    }
}

inline int piFunc(int x) {
    if (x <= 1) return 0;
    return piArray[x];
}

ll sumPrimeFloor(ll n) {
    if (n < 2) return 0;
    ll ans = 0, i = 2;
    while (i <= n) {
        ll v = n / i;
        ll i2 = n / v;
        if (i2 > n) i2 = n;
        ll cnt = piFunc((int)i2) - piFunc((int)(i - 1));
        ans += v * cnt;
        i = i2 + 1;
    }
    return ans;
}

int main() {
    cincout();
    computePi();
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << sumPrimeFloor(n) << '\n';
    }
    return 0;
}