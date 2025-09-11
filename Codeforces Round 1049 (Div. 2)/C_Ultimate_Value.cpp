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
   int n; input(n);
   vector<long long>a(n+1);
   rng(i,1,n+1) cin>>a[i];
   long long S=0;
   rng(i,1,n+1) S += (i&1)? a[i] : -a[i];
   long long best=0;
   int fo=-1, lo=-1, fe=-1, le=-1;
   rng(i,1,n+1){
      if(i&1){ if(fo==-1) fo=i; lo=i; }
      else{ if(fe==-1) fe=i; le=i; }
   }
   if(fo!=-1 && fo!=lo) best=max(best,(long long)(lo-fo));
   if(fe!=-1 && fe!=le) best=max(best,(long long)(le-fe));
   const long long INF = (1LL<<62);
   long long minOdd = INF, minEven = INF;
   rng(i,1,n+1){
      if(i&1){
         if(minEven<INF){
            long long cand = (long long)i - 2*a[i] - minEven;
            if(cand>best) best=cand;
         }
         long long val = (long long)i + 2*a[i];
         if(val<minOdd) minOdd=val;
      }else{
         if(minOdd<INF){
            long long cand = (long long)i + 2*a[i] - minOdd;
            if(cand>best) best=cand;
         }
         long long val = (long long)i - 2*a[i];
         if(val<minEven) minEven=val;
      }
   }
   print(S + max(0LL,best));
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