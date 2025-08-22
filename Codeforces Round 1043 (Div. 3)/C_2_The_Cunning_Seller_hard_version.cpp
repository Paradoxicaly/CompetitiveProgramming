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
   long long n,k; cin>>n>>k;
   vector<long long> p3(25,1);
   for(int i=1;i<25;i++) p3[i]=p3[i-1]*3LL;

   vector<long long> a(25,0);
   long long tmp=n;
   int L=0;
   while(tmp){
       a[L++] = tmp%3;
       tmp/=3;
   }
   long long S=0, F0=0;
   for(int i=0;i<L;i++){
       S += a[i];
       if(i>=1) F0 += 1LL*i*a[i]*p3[i];
   }
   if(k<S){ print(-1); return; }
   long long limit = min(k,n);
   if(((limit - S)&1)) --limit;
   long long t = (limit - S)/2;

   vector<long long> B(L+2,0);
   for(int j=L;j>=1;j--) B[j]=a[j]+3LL*B[j+1];

   long long take=0;
   for(int j=L;j>=1 && t>0;j--){
       long long s = min(t, B[j]);
       take += s * p3[j];
       t -= s;
   }
   long long Fbest = F0 - take;
   long long ans = 3LL*n + Fbest/3LL;
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