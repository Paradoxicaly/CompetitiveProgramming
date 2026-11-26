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
   vector<ll> a(n);
   ll o=0;
   for(auto&x:a){ cin>>x; o|=x; }
   int p0=__builtin_popcountll(o);
   vector<ll> f(40,LLONG_MAX);
   rep(c,p0+1) f[c]=0;
   rep(k,32){
       auto b=a;
       ll cost=0;
       for(int j=k;j>=0;j--){
           bool has=false;
           for(ll x:b) if(x>>j&1){ has=true; break; }
           if(has) continue;
           int bi=0; ll bc=LLONG_MAX;
           rep(i,n){ ll c=(((b[i]>>j)+1)<<j)-b[i]; if(c<bc){ bc=c; bi=i; } }
           cost+=bc; b[bi]+=bc;
       }
       int c=__builtin_popcountll(o|((1LL<<(k+1))-1));
       chmin(f[c],cost);
   }
   for(int c=38;c>=0;c--) chmin(f[c],f[c+1]);
   while(q--){
       ll b; cin>>b;
       int ans=0;
       rep(c,40) if(f[c]<=b) ans=c;
       print(ans);
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
