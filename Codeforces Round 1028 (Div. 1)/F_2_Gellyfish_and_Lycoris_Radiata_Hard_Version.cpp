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
mt19937 rnd(20251126);
vi lc,rc,sz_,pr,cv,own;
vector<char> rv,cl,alive;
vi tl,ps,val,nx;
int nobj(){ tl.pb(-1); ps.pb(-1); return sz(tl)-1; }
void app(int o,int v){
   val.pb(v); nx.pb(-1);
   int e=sz(val)-1;
   if(tl[o]!=-1) nx[tl[o]]=e;
   tl[o]=e;
   if(ps[o]==-1) ps[o]=e;
}
void addp(int c,int v){
   if(!cv[c]){ cv[c]=v; cl[c]=0; }
   else if(!cl[c]){ int o=nobj(); app(o,cv[c]); app(o,v); cv[c]=o; cl[c]=1; }
   else app(cv[c],v);
}
int fst(int o);
int fv(int v){ return v<0?(alive[-v]?-v:0):fst(v); }
int fst(int o){
   while(ps[o]!=-1){
       int r=fv(val[ps[o]]);
       if(r) return r;
       ps[o]=nx[ps[o]];
   }
   return 0;
}
void upd(int u){ sz_[u]=1+sz_[lc[u]]+sz_[rc[u]]; }
void push(int u){
   if(rv[u]){
       swap(lc[u],rc[u]);
       if(lc[u]) rv[lc[u]]^=1;
       if(rc[u]) rv[rc[u]]^=1;
       rv[u]=0;
   }
   if(cv[u]){
       int v=cv[u];
       app(own[u],v);
       if(lc[u]) addp(lc[u],v);
       if(rc[u]) addp(rc[u],v);
       cv[u]=0;
   }
}
void split(int u,int k,int&a,int&b){
   if(!u){ a=b=0; return; }
   push(u);
   if(sz_[lc[u]]<k){ split(rc[u],k-sz_[lc[u]]-1,rc[u],b); a=u; }
   else{ split(lc[u],k,a,lc[u]); b=u; }
   upd(u);
}
int mrg(int a,int b){
   if(!a||!b) return a|b;
   if(pr[a]>pr[b]){ push(a); rc[a]=mrg(rc[a],b); upd(a); return a; }
   push(b); lc[b]=mrg(a,lc[b]); upd(b); return b;
}
void solve(){
   int n,q; input(n,q);
   lc.assign(n+1,0); rc=lc; sz_=lc; pr=lc; cv=lc; own=lc;
   rv.assign(n+1,0); cl=rv; alive.assign(q+1,1);
   tl.reserve(1<<24); ps.reserve(1<<24); val.reserve(1<<25); nx.reserve(1<<25);
   nobj();
   int root=0;
   rng(i,1,n+1){ pr[i]=rnd(); sz_[i]=1; own[i]=nobj(); root=mrg(root,i); }
   int ans=0;
   string out;
   rng(i,1,q+1){
       int a,b,c; cin>>a>>b>>c;
       if(a==3){
           int x=(b+ans-1)%q+1;
           if(x<i) alive[x]=0;
       }else{
           int r=(b+ans-1)%n+1,L,R;
           split(root,r,L,R);
           if(a==1) addp(L,-i);
           else rv[L]^=1;
           root=mrg(L,R);
       }
       int p=(c+ans-1)%n+1,u=root;
       while(true){
           push(u);
           int ls=sz_[lc[u]];
           if(p<=ls) u=lc[u];
           else if(p==ls+1) break;
           else{ p-=ls+1; u=rc[u]; }
       }
       ans=fst(own[u]);
       out+=to_string(ans);
       out+='\n';
   }
   cout<<out;
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   solve();
   return 0;
}
