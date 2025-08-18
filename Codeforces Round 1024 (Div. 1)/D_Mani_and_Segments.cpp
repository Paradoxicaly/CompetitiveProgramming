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


ll power(ll a, ll b, ll m = MOD){
   ll res = 1 % m;
   a %= m;
   while(b > 0){
       if(b & 1) res = (res * a) % m;
       a = (a * a) % m;
       b >>= 1;
   }
   return res;
}


void solve(){
   int n; if(!(cin>>n)) return;
   vector<int>a(n+2,0);
   for(int i=1;i<=n;i++) cin>>a[i];

   vector<int> sl(n+2,0), bl(n+2,0), sr(n+2,n+1), br(n+2,n+1);
   vector<int> s, b;

   for(int i=1;i<=n;i++){
       while(!s.empty() && a[s.back()] > a[i]) s.pop_back();
       while(!b.empty() && a[b.back()] < a[i]) b.pop_back();
       sl[i] = s.empty()?0:s.back();
       bl[i] = b.empty()?0:b.back();
       s.pb(i); b.pb(i);
   }
   s.clear(); b.clear();
   for(int i=n;i>=1;i--){
       while(!s.empty() && a[s.back()] > a[i]) s.pop_back();
       while(!b.empty() && a[b.back()] < a[i]) b.pop_back();
       sr[i] = s.empty()?n+1:s.back();
       br[i] = b.empty()?n+1:b.back();
       s.pb(i); b.pb(i);
   }

   vector<int> R(n+2,n), L(n+2,1);
   R[n]=n;
   for(int i=n-1;i>=1;i--){
       R[i]=R[i+1];
       if(a[i]>a[i+1] && br[i+1]<=n && a[br[i+1]]<a[i]) R[i]=min(R[i], br[i+1]-1);
       if(a[i]<a[i+1] && sr[i+1]<=n && a[sr[i+1]]>a[i]) R[i]=min(R[i], sr[i+1]-1);
   }
   L[1]=1;
   for(int i=2;i<=n;i++){
       L[i]=L[i-1];
       if(a[i]>a[i-1] && bl[i-1]>=1 && a[bl[i-1]]<a[i]) L[i]=max(L[i], bl[i-1]+1);
       if(a[i]<a[i-1] && sl[i-1]>=1 && a[sl[i-1]]>a[i]) L[i]=max(L[i], sl[i-1]+1);
   }

   ll ans = R[1];
   for(int i=2;i<=n;i++){
       ans += (ll)(i-1 - L[i] + 1) * (ll)(R[i] - R[i-1]);
       ans += (ll)(R[i] - i + 1);
   }
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
