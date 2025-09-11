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
   int n; cin>>n;
   vector<long long> l(n), r(n), s(n);
   long long sumr=0, suml=0;
   rep(i,n){
      cin>>l[i]>>r[i];
      s[i]=l[i]+r[i];
      sumr+=r[i]; suml+=l[i];
   }
   vector<int> id(n); iota(all(id),0);
   sort(all(id), [&](int a,int b){ if(s[a]!=s[b]) return s[a]>s[b]; return a<b; });
   int m=n/2;
   long long Sm=0;
   rep(i,m) Sm+=s[id[i]];
   long long topPart=0;
   if(n%2==0){
      topPart=Sm;
   }else{
      long long sm1=s[id[m]];
      long long minr= (m? r[id[0]]: (long long)4e18);
      rep(i,m) if(r[id[i]]<minr) minr=r[id[i]];
      long long maxl=0;
      rng(i,m,n) if(l[id[i]]>maxl) maxl=l[id[i]];
      long long cand1 = (m? Sm + sm1 - minr : (long long)-9e18);
      long long cand2 = Sm + maxl;
      topPart = max(cand1,cand2);
   }
   long long ans = (sumr - 2*suml) + topPart;
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
