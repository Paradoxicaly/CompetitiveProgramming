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
   vi a(n);
   rep(i,n) input(a[i]);
   vi d1(n),d2(n);
   for(int i=0,l=0,r=-1;i<n;i++){
      int t=i>r?1:min(d1[l+r-i],r-i+1);
      while(i-t>=0&&i+t<n&&a[i-t]==a[i+t]) t++;
      d1[i]=t;
      if(i+t-1>r){ l=i-t+1; r=i+t-1; }
   }
   for(int i=0,l=0,r=-1;i<n;i++){
      int t=i>r?0:min(d2[l+r-i+1],r-i+1);
      while(i-t-1>=0&&i+t<n&&a[i-t-1]==a[i+t]) t++;
      d2[i]=t;
      if(i+t-1>r){ l=i-t; r=i+t-1; }
   }
   vector<char> bad(n+1);
   bad[a[n-1]]=1;
   rng(s,1,n){
      int L=n-s;
      bool ok=L%2?d1[s+L/2]>=L/2+1:d2[s+L/2]>=L/2;
      if(ok) bad[a[s-1]]=1;
   }
   int c1=1;
   while(bad[c1]) c1++;
   int c2=1;
   while(c2==c1||c2==a[n-1]) c2++;
   int c3=1;
   while(c3==c1||c3==c2) c3++;
   int c[3]={c1,c2,c3};
   rep(i,k) cout<<c[i%3]<<" \n"[i==k-1];
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
