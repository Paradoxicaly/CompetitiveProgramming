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
   vector<vector<unsigned long long>> s(n+1,vector<unsigned long long>(n+1)),a=s,b=s;
   rng(i,1,n+1) rng(j,1,n+1){
       unsigned long long x; cin>>x;
       s[i][j]=x+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
       a[i][j]=x*i+a[i-1][j]+a[i][j-1]-a[i-1][j-1];
       b[i][j]=x*j+b[i-1][j]+b[i][j-1]-b[i-1][j-1];
   }
   auto g=[&](auto&p,int x1,int y1,int x2,int y2){ return p[x2][y2]-p[x1-1][y2]-p[x2][y1-1]+p[x1-1][y1-1]; };
   string o;
   while(q--){
       int x1,y1,x2,y2; input(x1,y1,x2,y2);
       unsigned long long w=y2-y1+1,S=g(s,x1,y1,x2,y2);
       unsigned long long r=w*g(a,x1,y1,x2,y2)-w*x1*S+g(b,x1,y1,x2,y2)-(unsigned long long)(y1-1)*S;
       o+=to_string(r); o+=' ';
   }
   o.back()='\n';
   cout<<o;
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
