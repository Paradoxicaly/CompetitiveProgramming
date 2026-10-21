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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
void solve(){
   int n,m; input(n,m);
   vector<unsigned long long> h(n+2,0);
   set<pii> ex;
   rep(i,m){
       int l,r; input(l,r); ex.insert({l,r});
       unsigned long long z=rnd(); h[l]^=z; h[r+1]^=z;
   }
   rng(i,1,n+1) h[i]^=h[i-1];
   vi id(n);
   iota(all(id),1);
   sort(all(id),[&](int a,int b){ return h[a]!=h[b]?h[a]<h[b]:a<b; });
   vector<pii> sg,cl;
   for(int i=0,j;i<n;i=j){
       j=i;
       while(j<n&&h[id[j]]==h[id[i]]){ if(j>i) sg.pb({id[j-1],id[j]-1}); j++; }
       cl.pb({id[i],id[j-1]});
   }
   auto out=[&](vector<pii> v){
       print(sz(v));
       for(auto [l,r]:v) print(l,r);
   };
   auto build=[&](vi c){
       sort(all(c));
       int k=sz(c),hh=k/2;
       vector<pii> res;
       if(k&1){
           int md=c[hh];
           res.pb(ex.count({1,md})?pii(md+1,n):pii(1,md));
           c.erase(c.begin()+hh);
       }
       rep(i,hh) res.pb({c[i]+1,c[i+hh]});
       out(res);
   };
   if(sg.empty()){ print(0); return; }
   sort(all(sg),[&](pii a,pii b){ return a.se<b.se; });
   vi pts;
   int last=-1;
   for(auto [l,r]:sg) if(l>last){ pts.pb(r); last=r; }
   int k=sz(pts);
   if(k&1){ build(pts); return; }
   int minR=n,maxL=0;
   vi bst(n+2,n);
   for(auto [l,r]:sg){ chmin(minR,r); chmax(maxL,l); chmin(bst[l],r); }
   for(int x=n;x>=0;x--) chmin(bst[x],bst[x+1]);
   int LG=1;
   while((1<<LG)<=k) LG++;
   vector<vi> up(LG,vi(n+1,n));
   rng(x,0,n) up[0][x]=bst[x+1];
   rng(j,1,LG) rng(x,0,n+1) up[j][x]=up[j-1][up[j-1][x]];
   up[0][n]=n;
   rng(j,1,LG) up[j][n]=n;
   sort(all(cl));
   int mx=0,ptr=0;
   rng(c1,1,minR+1){
       while(ptr<sz(cl)&&cl[ptr].fi<=c1) chmax(mx,cl[ptr++].se);
       int q=c1,cnt=0;
       for(int j=LG-1;j>=0;j--) if(cnt+(1<<j)<=k-1&&up[j][q]<n){ q=up[j][q]; cnt+=1<<j; }
       int cm=cnt==k-1?q:n-1;
       if(cm<max(maxL,mx)||cm<=c1) continue;
       vi c={c1};
       int x=c1;
       rep(t,cnt){ x=up[0][x]; if(x<cm) c.pb(x); }
       c.pb(cm);
       if(sz(c)==k){ build(c); return; }
   }
   pts.pb(pts[0]==1?pts[0]:1);
   build(pts);
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
