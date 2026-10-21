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
const int MXN=400005*26+5;
int ch[MXN][2],cn[MXN],tot;
int ins(int p,int v){
   int r=++tot,c=r;
   for(int b=24;b>=0;b--){
       int x=v>>b&1;
       ch[c][0]=ch[p][0]; ch[c][1]=ch[p][1]; cn[c]=cn[p]+1;
       ch[c][x]=++tot;
       c=ch[c][x]; p=ch[p][x];
   }
   ch[c][0]=ch[c][1]=0; cn[c]=cn[p]+1;
   return r;
}
void solve(){
   int n; input(n);
   vi a(n+1),P(n+1,0);
   rng(i,1,n+1){ cin>>a[i]; P[i]=P[i-1]^a[i]; }
   tot=0;
   vector<array<int,2>> rt(n+1);
   rep(j,n+1){
       rt[j]=j?rt[j-1]:array<int,2>{0,0};
       rt[j][j&1]=ins(j?rt[j-1][j&1]:0,P[j]);
   }
   auto qry=[&](int x,int y,int p,int T,ll Z){
       int ra=rt[y][p],rb=x>0?rt[x-1][p]:0;
       ll res=0;
       for(int b=24;b>=0;b--){
           int t=T>>b&1;
           ll sb=cn[ch[ra][t^1]]-cn[ch[rb][t^1]];
           if(sb) res+=sb*(Z>>(b+1)<<(b+1));
           ra=ch[ra][t]; rb=ch[rb][t];
           if(cn[ra]-cn[rb]==0) return res;
       }
       return res+(ll)(cn[ra]-cn[rb])*Z;
   };
   vector<pii> cur,nx;
   unsigned long long ans=0;
   rng(r,1,n+1){
       nx.clear();
       nx.pb({a[r],r});
       for(auto [v,s]:cur){
           int w=v&a[r];
           if(w==nx.back().fi) nx.back().se=s;
           else nx.pb({w,s});
       }
       swap(cur,nx);
       int hi=r;
       for(auto [v,s]:cur){
           if(v) ans+=qry(s-1,hi-1,(r-1)&1,P[r]^v,v);
           hi=s-1;
       }
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
