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
ostream& operator<<(ostream &o, const vector<T> &v){ o<<"{"; for(int i=0;i<sz(v);i++) o<<(i?" ":"")<<v[i]; return o<<"}"; }
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

ll pw(ll a, ll b, ll m = MOD){
   ll r = 1 % m; a %= m;
   while(b > 0){
       if(b & 1) r = (r * a) % m;
       a = (a * a) % m;
       b >>= 1;
   }
   return r;
}

void solve(){
   int n; ll k; if(!(cin>>n>>k)) return;
   string s; cin>>s;
   vector<ll> a(n); rep(i,n) cin>>a[i];
   vi z; rep(i,n) if(s[i]=='0') z.pb(i);
   if(z.empty()){
      ll cur=a[0],best=a[0];
      rng(i,1,n){ cur=max(a[i],cur+a[i]); best=max(best,cur); }
      if(best==k){ cout<<"Yes\n"; rep(i,n) cout<<a[i]<<(i+1==n?'\n':' '); }
      else cout<<"No\n";
      return;
   }
   vector<ll> L(n,0),R(n,0);
   ll g=LLONG_MIN;
   for(int i=0;i<n;){
      if(s[i]=='1'){
         int Lb=i; while(i<n&&s[i]=='1') ++i; int Rb=i-1;
         ll pre=LLONG_MIN,suf=LLONG_MIN;
         ll t=0; for(int j=Lb;j<=Rb;++j){ t+=a[j]; pre=max(pre,t); }
         t=0; for(int j=Rb;j>=Lb;--j){ t+=a[j]; suf=max(suf,t); }
         ll cur=a[Lb],best=a[Lb];
         for(int j=Lb+1;j<=Rb;++j){ cur=max(a[j],cur+a[j]); best=max(best,cur); }
         g=max(g,best);
         if(Lb-1>=0&&s[Lb-1]=='0') R[Lb-1]=max(0LL,pre);
         if(Rb+1<n&&s[Rb+1]=='0') L[Rb+1]=max(0LL,suf);
      }else ++i;
   }
   if(g>k){ cout<<"No\n"; return; }
   vector<ll> b=a;
   const ll NEG=-1000000000000000000LL;
   for(int idx:z) b[idx]=NEG;
   if(g==k){
      cout<<"Yes\n";
      rep(i,n) cout<<b[i]<<(i+1==n?'\n':' ');
      return;
   }
   int id=z[0];
   b[id]=k-L[id]-R[id];
   cout<<"Yes\n";
   rep(i,n) cout<<b[i]<<(i+1==n?'\n':' ');
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