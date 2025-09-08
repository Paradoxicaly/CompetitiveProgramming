/*
Tomato_Cultivator
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using vi  = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)
 
const int MOD = 1e9+7;
 
template<class... T> void input(T&... a){ (cin>>...>>a); }
template<class T,class... Ts> void print(const T& a,const Ts&... b){ cout<<a; (cout<<...<<(cout<<' ',b)); cout<<'\n'; }
void print(){ cout<<'\n'; }
ll gcdll(ll a,ll b){ return b?gcdll(b,a%b):a; }
ll power(ll a, ll b, ll m = MOD){ ll res = 1 % m; a %= m; while(b > 0){ if(b & 1) res = (res * a) % m; a = (a * a) % m; b >>= 1; } return res; }
 
void solve(){
   int n,k; input(n,k);
   vector<vector<int>> g(n+1);
   for(int i=2;i<=n;i++){ int p; cin>>p; g[p].pb(i); }
   vector<int> dep(n+1,0);
   queue<int> q; q.push(1); dep[1]=1;
   while(!q.empty()){
       int v=q.front(); q.pop();
       for(int u: g[v]){ dep[u]=dep[v]+1; q.push(u); }
   }
   int mx=*max_element(all(dep));
   vector<int> cnt(mx+2,0);
   for(int i=1;i<=n;i++) cnt[dep[i]]++;
   int mindep=1e9;
   for(int i=1;i<=n;i++) if(g[i].empty()) mindep=min(mindep,dep[i]);
   vector<int> a;
   for(int d=1; d<=mindep; d++) a.pb(cnt[d]);
   int ones=n-k;
   int lim=n;
   bitset<1005> dp; dp[0]=1;
   int best=0, sum=0;
   for(int i=0;i<sz(a);i++){
       dp = dp | (dp<<a[i]);
       sum += a[i];
       int lo = max(0, sum - ones);
       int hi = min(k, sum);
       bool ok=false;
       for(int s=lo; s<=hi; s++) if(dp[s]){ ok=true; break; }
       if(ok) best=i+1;
   }
   print(best);
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
 
   int T=1;
   if(cin>>T){
       while(T--) solve();
   }
   return 0;
}