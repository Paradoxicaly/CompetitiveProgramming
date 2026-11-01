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
   int n; input(n);
   vi a(n),p;
   rep(i,n){ input(a[i]); if(a[i]!=-1) p.pb(i); }
   if(p.empty()){ rep(i,n) cout<<(i%2?2:1)<<" \n"[i==n-1]; return; }
   vi b=a;
   for(int i=p[0]-1;i>=0;i--) b[i]=(p[0]-i)%2?a[p[0]]*2:a[p[0]];
   rng(i,p.back()+1,n) b[i]=(i-p.back())%2?a[p.back()]*2:a[p.back()];
   rep(k,sz(p)-1){
      int l=p[k],r=p[k+1],x=a[l],y=a[r];
      vi u,v;
      while(x!=y){ if(x>y){ u.pb(x); x/=2; } else{ v.pb(y); y/=2; } }
      u.pb(x);
      reverse(all(v));
      for(int t:v) u.pb(t);
      int L=sz(u)-1,d=r-l;
      if(L>d||(d-L)%2){ print(-1); return; }
      rep(j,sz(u)) b[l+j]=u[j];
      rng(i,l+L+1,r+1) b[i]=(i-l-L)%2?a[r]*2:a[r];
   }
   rep(i,n) cout<<b[i]<<" \n"[i==n-1];
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
