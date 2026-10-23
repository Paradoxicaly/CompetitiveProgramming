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
const int MXN=200005*31;
int ch[MXN][2],mx[MXN],cnt;
void solve(){
   int n,k; input(n,k);
   vi a(n); rep(i,n) cin>>a[i];
   if(k==0){ print(1); return; }
   cnt=1; ch[0][0]=ch[0][1]=0; mx[0]=-1;
   int ans=INT_MAX;
   rep(r,n){
       int u=0,best=-1;
       for(int b=29;b>=0&&u>=0;b--){
           int x=a[r]>>b&1,y=k>>b&1;
           if(!y){ if(ch[u][x^1]) chmax(best,mx[ch[u][x^1]]); u=ch[u][x]?ch[u][x]:-1; }
           else u=ch[u][x^1]?ch[u][x^1]:-1;
       }
       if(u>=0) chmax(best,mx[u]);
       if(best>=0) chmin(ans,r-best+1);
       u=0;
       for(int b=29;b>=0;b--){
           int x=a[r]>>b&1;
           if(!ch[u][x]){ ch[u][x]=cnt; ch[cnt][0]=ch[cnt][1]=0; mx[cnt]=-1; cnt++; }
           u=ch[u][x]; mx[u]=r;
       }
   }
   print(ans==INT_MAX?-1:ans);
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
