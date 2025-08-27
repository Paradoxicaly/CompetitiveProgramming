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
void bug__(int c,A... a){
   cerr<<"\e[1;"<<c<<"m"; ((cerr<<a<<' '),...); cerr<<"\e[0m\n";
}
#define bug_(c,x...) bug__(c,__LINE__,"[" + string(#x) + "]",x)
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
   vector<vi> g(n+1);
   rep(i,n-1){
      int u,v; cin>>u>>v;
      g[u].pb(v); g[v].pb(u);
   }
   auto bfs=[&](int s){
      vi d(n+1,-1),p(n+1);
      queue<int>q; q.push(s); d[s]=0;
      while(!q.empty()){
         int v=q.front(); q.pop();
         for(int u:g[v]) if(d[u]==-1){
            d[u]=d[v]+1; p[u]=v; q.push(u);
         }
      }
      int best=s; rng(i,1,n+1) if(d[i]>d[best]) best=i;
      return tuple{best,d,p};
   };
   auto [U,d1,p1]=bfs(1);
   auto [V,dU,pU]=bfs(U);
   int diam=*max_element(all(dU));
   if(diam==n-1){ print(-1); return; }
   vector<char> far(n+1);
   rng(i,1,n+1) if(dU[i]==diam) far[i]=1;
   int a=-1,b=-1,c=-1;
   function<bool(int,int)> dfs=[&](int v,int p){
      bool has=far[v];
      vi ch; vi hf;
      for(int u:g[v]) if(u!=p){
         bool h=dfs(u,v);
         has|=h; ch.pb(u); hf.pb(h);
      }
      if(p&&has&&sz(ch)>=2){
         int idxf=-1,idxo=-1;
         rep(i,sz(ch)) if(hf[i]&&idxf==-1) idxf=i;
         rep(i,sz(ch)) if(i!=idxf){ idxo=i; break; }
         if(idxf!=-1&&idxo!=-1){ a=p; b=v; c=ch[idxo]; }
      }
      return has;
   };
   dfs(U,0);
   if(b==-1){
      rng(v,1,n+1) if(sz(g[v])>=3){
         a=g[v][0]; b=v; c=g[v][1]; break;
      }
   }
   if(b==-1) print(-1);
   else print(a,b,c);
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
