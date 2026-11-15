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
const ll NEG=LLONG_MIN/4;
struct seg{
   int n; vector<ll> t,lz;
   seg(int n):n(n),t(4*n,NEG),lz(4*n,0){}
   void ap(int x,ll v){ t[x]+=v; lz[x]+=v; }
   void pd(int x){ if(lz[x]){ ap(2*x,lz[x]); ap(2*x+1,lz[x]); lz[x]=0; } }
   void add(int x,int l,int r,int ql,int qr,ll v){
       if(qr<l||r<ql) return;
       if(ql<=l&&r<=qr){ ap(x,v); return; }
       pd(x); int md=(l+r)/2;
       add(2*x,l,md,ql,qr,v); add(2*x+1,md+1,r,ql,qr,v);
       t[x]=max(t[2*x],t[2*x+1]);
   }
   void set(int x,int l,int r,int p,ll v){
       if(l==r){ t[x]=v; return; }
       pd(x); int md=(l+r)/2;
       if(p<=md) set(2*x,l,md,p,v); else set(2*x+1,md+1,r,p,v);
       t[x]=max(t[2*x],t[2*x+1]);
   }
   ll qry(int x,int l,int r,int ql,int qr){
       if(qr<l||r<ql) return NEG;
       if(ql<=l&&r<=qr) return t[x];
       pd(x); int md=(l+r)/2;
       return max(qry(2*x,l,md,ql,qr),qry(2*x+1,md+1,r,ql,qr));
   }
};
void solve(){
   int n; input(n);
   vector<ll> v(n+1);
   vi a(n),pb(n+1);
   rng(i,1,n+1) cin>>v[i];
   for(auto&x:a) cin>>x;
   rep(i,n){ int x; cin>>x; pb[x]=i+1; }
   seg sg(n+1);
   sg.set(1,0,n,0,0);
   for(int x:a){
       int q=pb[x];
       ll mx=sg.qry(1,0,n,0,q-1);
       sg.add(1,0,n,0,q-1,v[x]);
       sg.set(1,0,n,q,mx);
   }
   print(sg.t[1]);
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
