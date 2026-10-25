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
   int n,m; input(n,m);
   vector<ll> a(n),b(m);
   for(auto&x:a) cin>>x;
   for(auto&x:b) cin>>x;
   sort(all(a)); sort(all(b));
   vector<ll> A(n/2+1,0),B(m/2+1,0);
   rng(i,1,n/2+1) A[i]=A[i-1]+a[n-i]-a[i-1];
   rng(i,1,m/2+1) B[i]=B[i-1]+b[m-i]-b[i-1];
   vector<ll> res;
   for(int k=1;;k++){
       int lo=max(0,2*k-m),hi=min(k,n-k);
       if(lo>hi) break;
       auto g=[&](int p){ return A[p]+B[k-p]; };
       while(hi-lo>2){
           int m1=lo+(hi-lo)/3,m2=hi-(hi-lo)/3;
           if(g(m1)<g(m2)) lo=m1+1; else hi=m2;
       }
       ll best=g(lo);
       rng(p,lo+1,hi+1) chmax(best,g(p));
       res.pb(best);
   }
   print(sz(res));
   string o;
   rep(i,sz(res)){ o+=to_string(res[i]); o+=i+1<sz(res)?' ':'\n'; }
   if(sz(res)) cout<<o;
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
