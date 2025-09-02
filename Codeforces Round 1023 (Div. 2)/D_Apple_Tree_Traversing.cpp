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

#ifdef Tomato
template<class T>
ostream& operator<<(ostream &o, const vector<T> &v){
   o<<"{"; for(int i=0;i<sz(v);i++) o<<(i?" ":"")<<v[i]; return o<<"}";
}
template<class A,class B>
ostream& operator<<(ostream &o,const pair<A,B>&p){ return o<<"("<<p.fi<<","<<p.se<<")"; }
template<class... A>
void bug(int c,A... a){
   cerr<<"\e[1;"<<c<<"m"; ((cerr<<a<<' '),...); cerr<<"\e[0m\n";
}
#define bug_(c,x...) bug(c,LINE,"[" + string(#x) + "]",x)
#define bug(x...) bug_(32,x)
#else
#define bug(x...) ((void)0)
#endif

template<class... T>
constexpr auto min(T... a){ return std::min({a...}); }
template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }

template<class... T> void input(T&... a){ (cin>>...>>a); }

template<class T,class... Ts>
void print(const T& a,const Ts&... b){
   cout<<a; (cout<<...<<(cout<<' ',b)); cout<<'\n';
}
void print(){ cout<<'\n'; }

template<class T> bool chmin(T& a,const T& b){ if(b<a){a=b; return true;} return false; }
template<class T> bool chmax(T& a,const T& b){ if(a<b){a=b; return true;} return false; }

ll gcdll(ll a,ll b){ return b?gcdll(b,a%b):a; }

ll power(ll a, ll b, ll m = MOD){
   ll res = 1 % m;
   a %= m;
   while(b > 0){
       if(b & 1) res = (res * a) % m;
       a = (a * a) % m;
       b >>= 1;
   }
   return res;
}

void solve(){
   int n; if(!(cin>>n)) return;
   vector<vector<int>> g(n+1);
   rep(i,n-1){ int u,v; cin>>u>>v; g[u].pb(v); g[v].pb(u); }
   vector<char> alive(n+1,1);
   vector<int> dist(n+1,0), par(n+1, -1), vis(n+1,0);
   int tick=1, rem=n;
   auto bfs_far = [&](int s, vector<int>* store_par)->pair<int,int>{
       tick++;
       queue<int> q;
       q.push(s);
       vis[s]=tick;
       dist[s]=0;
       if(store_par) (*store_par)[s]=-1;
       int bestD=0,bestV=s;
       while(!q.empty()){
           int v=q.front(); q.pop();
           if(dist[v]>bestD || (dist[v]==bestD && v>bestV)) bestD=dist[v], bestV=v;
           for(int w:g[v]){
               if(!alive[w]) continue;
               if(vis[w]==tick) continue;
               vis[w]=tick;
               dist[w]=dist[v]+1;
               if(store_par) (*store_par)[w]=v;
               q.push(w);
           }
       }
       return {bestD,bestV};
   };
   vector<array<int,3>> out;
   while(rem){
       for(int i=1;i<=n;i++){
           if(!alive[i]) continue;
           auto p1=bfs_far(i,nullptr);
           auto p2=bfs_far(p1.second,&par);
           int a=p1.second,b=p2.second;
           int len=p2.first+1;
           int u=max(a,b), v=min(a,b);
           out.push_back({len,u,v});
           int cur=b;
           while(true){
               alive[cur]=0; rem--;
               if(cur==a) break;
               cur=par[cur];
           }
       }
   }
   sort(all(out),greater<array<int,3>>());
   for(int i=0;i<sz(out);i++){
       cout<<out[i][0]<<' '<<out[i][1]<<' '<<out[i][2];
       if(i+1<sz(out)) cout<<' ';
   }
   cout<<'\n';
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
