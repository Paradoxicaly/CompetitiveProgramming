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
const ll INF=LLONG_MAX/4;
using mat=vector<vector<ll>>;
ll ad(ll x,ll y){ return (x>=INF||y>=INF)?INF:x+y; }
mat mul(const mat&A,const mat&B){
   int n=sz(A);
   mat C(n,vector<ll>(n,INF));
   rep(i,n) rep(k,n) if(A[i][k]<INF) rep(j,n) chmin(C[i][j],ad(A[i][k],B[k][j]));
   return C;
}
vector<ll> vmul(const vector<ll>&d,const mat&M){
   int n=sz(d);
   vector<ll> e(n,INF);
   rep(i,n) if(d[i]<INF) rep(j,n) chmin(e[j],ad(d[i],M[i][j]));
   return e;
}
void solve(){
   int n; ll m; input(n,m);
   vi a(n),b(n);
   for(auto&x:a) cin>>x;
   for(auto&x:b) cin>>x;
   int L=1;
   rep(i,n) L=lcm(L,a[i]);
   auto sf=[&](int x,int ph){ return x%a[ph]!=b[ph]; };
   auto cl=[&](vector<ll>&d,int x){
       rep(it,2*n){
           int ph=it%n;
           if(d[ph]<INF&&sf(x,ph)) chmin(d[(ph+1)%n],d[ph]+1);
       }
   };
   auto st=[&](const vector<ll>&d,int x){
       vector<ll> e(n,INF);
       int y=(x+1)%L;
       rep(ph,n) if(d[ph]<INF&&sf(y,ph)) chmin(e[(ph+1)%n],d[ph]+1);
       cl(e,y);
       return e;
   };
   mat M(n);
   rep(r,n){
       vector<ll> d(n,INF);
       d[r]=0;
       rep(x,L) d=st(d,x);
       M[r]=d;
   }
   vector<ll> d(n,INF);
   d[0]=0;
   cl(d,0);
   ll q=m/L;
   int rm=m%L;
   while(q){
       if(q&1) d=vmul(d,M);
       M=mul(M,M);
       q>>=1;
   }
   rep(x,rm) d=st(d,x);
   ll ans=*min_element(all(d));
   print(ans>=INF?-1:ans);
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
