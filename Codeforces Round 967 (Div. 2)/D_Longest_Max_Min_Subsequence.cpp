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
   vi a(n),lst(n+1,-1);
   rep(i,n){ input(a[i]); lst[a[i]]=i; }
   set<int> ls;
   rng(v,1,n+1) if(lst[v]>=0) ls.insert(lst[v]);
   vector<char> u(n+1);
   priority_queue<pii> mx;
   priority_queue<pii,vector<pii>,greater<pii>> mn;
   vi b;
   int cur=0,r=0;
   while(!ls.empty()){
      int R=*ls.begin();
      while(r<=R){ mx.push({a[r],-r}); mn.push({a[r],r}); r++; }
      int p;
      if(sz(b)%2==0){
         while(u[mx.top().fi]||-mx.top().se<cur) mx.pop();
         p=-mx.top().se;
      }else{
         while(u[mn.top().fi]||mn.top().se<cur) mn.pop();
         p=mn.top().se;
      }
      b.pb(a[p]); u[a[p]]=1; ls.erase(lst[a[p]]); cur=p+1;
   }
   print(sz(b));
   rep(i,sz(b)) cout<<b[i]<<" \n"[i==sz(b)-1];
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
