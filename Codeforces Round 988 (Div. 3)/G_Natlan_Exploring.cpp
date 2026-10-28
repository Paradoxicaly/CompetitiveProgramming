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
   const ll M=998244353;
   int n; input(n);
   const int V=1000001;
   vi sp(V,0);
   rng(i,2,V) if(!sp[i]) for(int j=i;j<V;j+=i) if(!sp[j]) sp[j]=i;
   vector<ll> S(V,0);
   ll dp=0;
   rep(i,n){
       int x; input(x);
       vi pr;
       while(x>1){ int p=sp[x]; pr.pb(p); while(x%p==0) x/=p; }
       int k=sz(pr);
       vector<pair<int,int>> ds;
       rng(m,1,1<<k){
           int d=1,c=0;
           rep(b,k) if(m>>b&1){ d*=pr[b]; c++; }
           ds.pb({d,c});
       }
       if(i==0) dp=1;
       else{
           dp=0;
           for(auto [d,c]:ds) dp=(dp+(c%2?S[d]:M-S[d]))%M;
       }
       for(auto [d,c]:ds) S[d]=(S[d]+dp)%M;
   }
   print(dp);
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   solve();
   return 0;
}
