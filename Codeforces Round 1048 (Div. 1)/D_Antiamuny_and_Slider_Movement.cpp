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
   int n,q; ll m; input(n,m,q);
   vector<ll> b(n+1);
   rng(i,1,n+1){ cin>>b[i]; b[i]-=i; }
   vector<pair<ll,int>> op(q);
   for(auto&[y,i]:op){ ll x; cin>>i>>x; y=x-i; }
   sort(all(op));
   vector<ll> iv(q+2,1);
   rng(i,2,q+2) iv[i]=(MOD-MOD/i)*iv[MOD%i]%MOD;
   ll fq=1;
   rng(i,1,q+1) fq=fq*i%MOD;
   vi le(n+2,0),ge(n+2,0);
   for(auto [y,i]:op){ le[i]++; ge[i]++; }
   rng(i,1,n+1) le[i]+=le[i-1];
   for(int i=n;i>=1;i--) ge[i]+=ge[i+1];
   string out;
   rng(k,1,n+1){
       int c1=le[k],c0=0;
       ll e=0,L=1;
       auto seg=[&](ll L,ll R){
           if(L>R) return;
           int tt=c1+c0;
           if(tt) e=(e+(R-L+1)%MOD*c1%MOD*iv[tt])%MOD;
           else if(b[k]>=L) e=(e+min(R,b[k])-L+1)%MOD;
       };
       for(int t=0;t<q;){
           int u=t;
           while(u<q&&op[u].fi==op[t].fi) u++;
           seg(L,op[t].fi);
           L=op[t].fi+1;
           rng(z,t,u){ int i=op[z].se; if(i<=k) c1--; if(i>=k) c0++; }
           t=u;
       }
       if(c0==0&&b[k]>=L) e=(e+b[k]-L+1)%MOD;
       ll r=(e+k)%MOD*fq%MOD;
       out+=to_string(r);
       out+=k==n?'\n':' ';
   }
   cout<<out;
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
