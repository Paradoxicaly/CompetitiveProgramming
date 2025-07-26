/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll   = long long;
using ull  = unsigned long long;
using pii  = pair<int,int>;
using pll  = pair<ll,ll>;
using vi   = vector<int>;
using vll  = vector<ll>;
using vb   = vector<bool>;
#define pb      push_back
#define fi      first
#define se      second
#define all(x)  begin(x), end(x)
#define sz(x)   ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)

void solve() {
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vll p(n); rep(i,n) cin >> p[i];
        vi d(n); rep(i,n) cin >> d[i];
        int q; cin >> q;
        vll a(q); rep(i,q) cin >> a[i];

        int S = n * 2 * k;
        vi nxt(S, -1), st(S);
        vb out(S);

        auto id = [&](int i, int dir, int r) {
            return ((i*2 + dir) * k) + r;
        };

        rep(i,n) rep(dir,2) rep(r,k) {
            bool flip = (r == d[i]);
            int dir2 = flip ? (dir^1) : dir;
            int cur = id(i, dir, r);
            if ((dir2==0 && i==0) || (dir2==1 && i==n-1)) {
                nxt[cur] = -1;
            } else {
                int j = dir2 ? i+1 : i-1;
                ll diff = llabs(p[j] - p[i]) % k;
                int r2 = (r + diff) % k;
                nxt[cur] = id(j, dir2, r2);
            }
        }

        rep(s,S) if (!st[s]) {
            vi seq;
            int v = s;
            while (v != -1 && st[v] == 0) {
                st[v] = 1;
                seq.pb(v);
                v = nxt[v];
            }
            bool res;
            if (v == -1)        res = true;
            else if (st[v] == 1) res = false;
            else                 res = out[v];
            for (int u : seq) {
                st[u] = 2;
                out[u] = res;
            }
        }

        for (ll x : a) {
            if (x > p.back()) {
                cout << "YES\n";
            } else {
                int idx = int(lower_bound(all(p), x) - p.begin());
                int s0;
                if (x == p[idx]) {
                    s0 = id(idx, 1, 0);
                } else {
                    ll dist = p[idx] - x;
                    int r = dist % k;
                    s0 = id(idx, 1, r);
                }
                cout << (out[s0] ? "YES\n" : "NO\n");
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}