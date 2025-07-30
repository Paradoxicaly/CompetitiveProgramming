/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define pb push_back
#define all(x) begin(x), end(x)
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)

void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> b(n+1);
    rng(i,1,n+1) cin >> b[i];
    vector<int> x(q), y(q), z(q);
    int maxId = n;
    vector<int> pos(n+1);
    rng(i,1,n+1) pos[i] = i;
    vector<vector<int>> rev_adj(n + q + 1);
    rep(i,q){
        cin >> x[i] >> y[i] >> z[i];
        int px = pos[x[i]], py = pos[y[i]];
        int u = ++maxId;
        rev_adj[u].pb(px);
        rev_adj[u].pb(py);
        pos[z[i]] = u;
    }
    vector<int> dp(maxId+1, 0);
    rng(i,1,n+1) dp[pos[i]] = b[i];
    for(int u = maxId; u >= 1; --u){
        for(int v: rev_adj[u]){
            dp[v] = max(dp[v], dp[u]);
        }
    }
    vector<int> a(n+1);
    rng(i,1,n+1) a[i] = dp[i];
    vector<int> c = a;
    rep(i,q){
        c[z[i]] = min(c[x[i]], c[y[i]]);
    }
    bool ok = true;
    rng(i,1,n+1) if(c[i] != b[i]) { ok = false; break; }
    if(!ok){
        cout << "-1\n";
        return;
    }
    rng(i,1,n+1){
        cout << a[i] << (i==n?'\n':' ');
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}