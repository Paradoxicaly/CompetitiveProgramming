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
vector<pair<ll,char>> rd(int k){
   vector<pair<ll,char>> v;
   rep(i,k){
       ll l; char d,c; cin>>l>>d>>c;
       if(!v.empty()&&v.back().se==c) v.back().fi+=l;
       else v.pb({l,c});
   }
   return v;
}
void solve(){
   int n,m; input(n,m);
   auto t=rd(n),s=rd(m);
   n=sz(t); m=sz(s);
   ll ans=0;
   if(m==1){
       for(auto [l,c]:t) if(c==s[0].se&&l>=s[0].fi) ans+=l-s[0].fi+1;
   }else if(m==2){
       rep(i,n-1) if(t[i].se==s[0].se&&t[i].fi>=s[0].fi&&t[i+1].se==s[1].se&&t[i+1].fi>=s[1].fi) ans++;
   }else{
       vector<pair<ll,char>> p(s.begin()+1,s.end()-1);
       int k=sz(p);
       vi fl(k,0);
       rng(i,1,k){
           int j=fl[i-1];
           while(j&&p[i]!=p[j]) j=fl[j-1];
           if(p[i]==p[j]) j++;
           fl[i]=j;
       }
       int j=0;
       rng(i,1,n-1){
           while(j&&t[i]!=p[j]) j=fl[j-1];
           if(t[i]==p[j]) j++;
           if(j==k){
               int st=i-k+1;
               auto L=t[st-1],R=t[i+1];
               if(L.se==s[0].se&&L.fi>=s[0].fi&&R.se==s[m-1].se&&R.fi>=s[m-1].fi) ans++;
               j=fl[j-1];
           }
       }
   }
   print(ans);
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   solve();
   return 0;
}
