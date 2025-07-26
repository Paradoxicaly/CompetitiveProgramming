/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll   = long long;
using pii  = pair<int,int>;
using vi   = vector<int>;
#define pb      push_back
#define fi      first
#define se      second
#define all(x)  begin(x), end(x)
#define sz(x)   ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)

void solve() {
    int n; ll k;
    cin >> n >> k;
    vector<ll> p(n), d(n);
    rep(i,n) cin >> p[i];
    rep(i,n) cin >> d[i];

    int S = 2*n;
    vector<int> nxt(S, -1);
    map<ll,int> f;
    for(int i=n-1;i>=0;--i){
        ll v = (d[i] - p[i] % k + k) % k;
        if(f.count(v)) nxt[n + i] = f[v];
        f[v] = i;
    }
    f.clear();
    rep(i,n){
        ll v = (d[i] + p[i]) % k;
        if(f.count(v)) nxt[i] = n + f[v];
        f[v] = i;
    }

    vector<vector<int>> adj(S);
    queue<int> que;
    vector<bool> out(S,false);
    rep(i,S){
        if(nxt[i]==-1){
            out[i]=true;
            que.push(i);
        } else {
            adj[nxt[i]].pb(i);
        }
    }
    while(!que.empty()){
        int x=que.front(); que.pop();
        for(int y: adj[x]){
            out[y]=true;
            que.push(y);
        }
    }

    map<ll, vector<pair<ll,int>>> mp;
    rep(i,n){
        ll v=(p[i]-d[i]+k)%k;
        mp[v].pb({p[i],i});
    }
    for(auto &kv: mp) sort(all(kv.second));

    int q; cin>>q;
    while(q--){
        ll a; cin>>a;
        ll mv = a % k;
        if(!mp.count(mv) || mp[mv].back().first < a){
            cout<<"YES\n";
            continue;
        }
        auto &vec = mp[mv];
        auto it = lower_bound(all(vec), make_pair(a,0));
        int idx = it->second;
        cout<<(out[idx]?"YES\n":"NO\n");
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}