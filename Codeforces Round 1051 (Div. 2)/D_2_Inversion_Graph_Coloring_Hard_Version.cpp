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
const int M=1e9+7;
void solve(){
   int n; input(n);
   int N=n+1;
   vector<vi> rb(N,vi(N+1,0)),cb(N,vi(N+1,0));
   auto add=[&](vi&b,int i,int v){ for(i++;i<=N;i+=i&-i){ b[i]+=v; if(b[i]>=M) b[i]-=M; } };
   auto qry=[&](vi&b,int i){ ll s=0; for(i++;i>0;i-=i&-i) s+=b[i]; return (int)(s%M); };
   add(rb[0],0,1); add(cb[0],0,1);
   ll tot=1;
   rep(t,n){
       int v; cin>>v;
       vi A(v+1),B(N);
       rep(y,v+1) A[y]=qry(cb[y],v);
       rng(x,v+1,N) B[x]=qry(rb[x],v);
       rep(y,v+1) if(A[y]){ add(rb[v],y,A[y]); add(cb[y],v,A[y]); tot+=A[y]; }
       rng(x,v+1,N) if(B[x]){ add(rb[x],v,B[x]); add(cb[v],x,B[x]); tot+=B[x]; }
       tot%=M;
   }
   print(tot);
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
