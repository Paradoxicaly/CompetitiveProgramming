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
ll pw(ll a,ll b,ll m=MOD){
   ll r=1%m; a%=m;
   while(b>0){ if(b&1) r=r*a%m; a=a*a%m; b>>=1; }
   return r;
}
void solve(){
   int n,q; input(n,q);
   rng(i,2,n+1){ int x; input(x); }
   vi p(n+2),ps(n+1),ss(n+2);
   rng(i,1,n+1){ input(p[i]); ps[p[i]]=i; }
   for(int v=n;v>=1;v--) ss[v]=2*v<=n?1+ss[2*v]+ss[2*v+1]:1;
   auto ok=[&](int v){
      if(2*v>n) return true;
      int i=ps[v],j=i+1+ss[2*v];
      if(j>n) return false;
      int a=p[i+1],b=p[j];
      return min(a,b)==2*v&&max(a,b)==2*v+1;
   };
   vector<char> g(n+1);
   int c=0;
   rng(v,1,n+1){ g[v]=ok(v); c+=g[v]; }
   while(q--){
      int x,y; input(x,y);
      int u=p[x],w=p[y];
      vi st={u,w,u/2,w/2};
      sort(all(st)); st.erase(unique(all(st)),st.end());
      swap(p[x],p[y]); ps[p[x]]=x; ps[p[y]]=y;
      for(int v:st) if(v>=1){ c-=g[v]; g[v]=ok(v); c+=g[v]; }
      print(c==n&&p[1]==1?"YES":"NO");
   }
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
