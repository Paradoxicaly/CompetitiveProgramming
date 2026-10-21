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
int n,K;
string a;
vi memo,stp;
int stamp;
int key(int u,int d,int l,int r,int z){ return (((u*n+d)*n+l)*n+r)*(K+1)+z; }
bool f(int u,int d,int l,int r,int z){
   int h=u+d+1,w=l+r+1;
   if(h==1&&w==1) return z<=1;
   int k=key(u,d,l,r,z);
   if(stp[k]==stamp) return memo[k];
   stp[k]=stamp;
   bool ok=false;
   int S=h*w-z;
   if(S>=0){
       char c=a[S];
       int nu=u,nd=d,nl=l,nr=r,ln=0;
       if(c=='U'&&u) nu--,ln=w;
       else if(c=='D'&&d) nd--,ln=w;
       else if(c=='L'&&l) nl--,ln=h;
       else if(c=='R'&&r) nr--,ln=h;
       if(ln) for(int dz=0;dz<=min(z,ln)&&!ok;dz++) ok=f(nu,nd,nl,nr,z-dz);
   }
   return memo[k]=ok;
}
void solve(){
   input(n);
   K=n==3?9:24;
   a.assign(n*n+1,'U');
   vi A;
   int h=n,w=n;
   rep(t,2*n-2){ A.pb(h*w); if(t%2==0) h--; else w--; }
   rep(t,2*n-2) rep(z,K+1){
       int S=A[t]-z;
       if(S>=0&&(t+1==2*n-2||S>A[t+1])) a[S]=(t%2==0?"UD":"LR")[z&1];
   }
   memo.assign(n*n*n*n*(K+1),0); stp.assign(sz(memo),0);
   rng(r,1,n+1) rng(c,1,n+1){
       stamp++;
       int z0=0;
       while(!f(r-1,n-r,c-1,n-c,z0)) z0++;
       vector<string> g(n,string(n,'1'));
       int x0=1,x1=n,y0=1,y1=n,u=r-1,d=n-r,l=c-1,rr=n-c,z=z0;
       while(x0<x1||y0<y1){
           int H=x1-x0+1,W=y1-y0+1;
           char ch=a[H*W-z];
           int nu=u,nd=d,nl=l,nr=rr,ln;
           vector<pii> cells;
           if(ch=='U'){ nu--; ln=W; rep(j,W) cells.pb({x0,y0+j}); }
           else if(ch=='D'){ nd--; ln=W; rep(j,W) cells.pb({x1,y0+j}); }
           else if(ch=='L'){ nl--; ln=H; rep(i,H) cells.pb({x0+i,y0}); }
           else{ nr--; ln=H; rep(i,H) cells.pb({x0+i,y1}); }
           int dz=0;
           while(!f(nu,nd,nl,nr,z-dz)) dz++;
           rep(i,dz) g[cells[i].fi-1][cells[i].se-1]='0';
           z-=dz; u=nu; d=nd; l=nl; rr=nr;
           if(ch=='U') x0++; else if(ch=='D') x1--; else if(ch=='L') y0++; else y1--;
       }
       if(z) g[r-1][c-1]='0';
       for(auto&s:g) print(s);
       print();
   }
   print(a);
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   solve();
   return 0;
}
