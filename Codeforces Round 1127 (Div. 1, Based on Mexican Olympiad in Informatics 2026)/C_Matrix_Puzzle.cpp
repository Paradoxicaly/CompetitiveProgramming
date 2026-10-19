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
   vector<vector<ll>> d(n+2,vector<ll>(n+2,0));
   rng(i,1,n+1) rng(j,1,n+1){ ll x; cin>>x; d[i][j]=-x; }
   rng(i,1,n+1) rng(j,1,n+1){ ll x; cin>>x; d[i][j]+=x; }
   int m=n-1;
   vector<vector<ll>> e(m+1,vector<ll>(m+1,0));
   vector<vector<int>> f(m+1,vector<int>(m+1,0));
   rng(i,1,m+1) rng(j,1,m+1){
       e[i][j]=d[i][j]-d[i+1][j]-d[i][j+1]+d[i+1][j+1];
       f[i][j]=e[i][j]!=0;
   }
   rng(i,1,m+1) rng(j,1,m+1){ int k=j+(j&-j); if(k<=m) f[i][k]+=f[i][j]; }
   rng(i,1,m+1){ int k=i+(i&-i); if(k<=m) rng(j,1,m+1) f[k][j]+=f[i][j]; }
   auto add=[&](int x,int y,int v){
       for(int i=x;i<=m;i+=i&-i) for(int j=y;j<=m;j+=j&-j) f[i][j]+=v;
   };
   auto qry=[&](int x,int y){
       int s=0;
       for(int i=x;i>0;i-=i&-i) for(int j=y;j>0;j-=j&-j) s+=f[i][j];
       return s;
   };
   auto upd=[&](int i,int j,ll v){
       if(i<1||i>m||j<1||j>m) return;
       bool o=e[i][j]!=0;
       e[i][j]+=v;
       bool w=e[i][j]!=0;
       if(o!=w) add(i,j,w?1:-1);
   };
   while(q--){
       char c; int r1,c1,r2,c2; input(c,r1,c1,r2,c2);
       if(c=='U'){
           ll x; cin>>x;
           upd(r1-1,c1-1,-x); upd(r1-1,c2,x); upd(r2,c1-1,x); upd(r2,c2,-x);
       }else{
           if(r1==r2||c1==c2){ print("YES"); continue; }
           int s=qry(r2-1,c2-1)-qry(r1-1,c2-1)-qry(r2-1,c1-1)+qry(r1-1,c1-1);
           print(s?"NO":"YES");
       }
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
