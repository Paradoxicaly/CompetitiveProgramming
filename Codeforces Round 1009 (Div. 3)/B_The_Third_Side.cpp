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

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define rrep(i,a,b) for (int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        rep(i, n) cin >> a[i];

        if (n == 1) {
            cout << a[0] << '\n';
            continue;
        }

        priority_queue<ll> pq;
        for (ll x : a) pq.push(x);

        while (pq.size() > 1) {
            ll x = pq.top(); pq.pop();
            ll y = pq.top(); pq.pop();
            ll z = x + y - 1;
            pq.push(z);
        }

        cout << pq.top() << '\n';
    }
    return 0;
}