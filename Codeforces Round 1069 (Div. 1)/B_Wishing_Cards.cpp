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
   int n,k; input(n,k);
   vi a(n); for(auto&x:a) cin>>x;
   vi ps; int mx=0;
   rep(i,n) if(a[i]>mx){ mx=a[i]; ps.pb(i); }
   const ll NEG=LLONG_MIN/4;
   vector<vector<ll>> dp(k+1,vector<ll>(k+1,NEG));
   dp[0][0]=0;
   rep(t,sz(ps)){
       int p=ps[t]; ll L=(t+1<sz(ps)?ps[t+1]:n)-p;
       auto nd=dp;
       rep(s,k+1) rep(c,s+1) if(nd[s][c]>NEG) nd[s][c]+=c*L;
       rep(s,k+1){
           ll bs=NEG;
           for(int v=1;v<=a[p]&&s+v<=k;v++){
               chmax(bs,dp[s][v-1]);
               if(bs>NEG) chmax(nd[s+v][v],bs+v*L);
           }
       }
       dp.swap(nd);
   }
   ll ans=0;
   rep(s,k+1) rep(c,s+1) chmax(ans,dp[s][c]);
   print(ans);
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
