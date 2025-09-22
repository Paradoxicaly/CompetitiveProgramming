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

struct Seg{
   int N;
   vector<int> t,lz;
   void init(int n){
       N=1; while(N<n) N<<=1;
       t.assign(2*N,0);
       lz.assign(2*N,0);
   }
   void apply(int p,int v){ t[p]+=v; lz[p]+=v; }
   void push(int p){
       if(lz[p]){
           apply(p<<1,lz[p]);
           apply(p<<1|1,lz[p]);
           lz[p]=0;
       }
   }
   void add(int p,int l,int r,int ql,int qr,int v){
       if(ql>r||qr<l) return;
       if(ql<=l&&r<=qr){ apply(p,v); return; }
       push(p);
       int m=(l+r)>>1;
       add(p<<1,l,m,ql,qr,v);
       add(p<<1|1,m+1,r,ql,qr,v);
       t[p]=max(t[p<<1],t[p<<1|1]);
   }
   void add(int l,int r,int v){
       if(l>r) return;
       add(1,0,N-1,l,r,v);
   }
   void setv(int p,int l,int r,int idx,int v){
       if(l==r){ t[p]=v; lz[p]=0; return; }
       push(p);
       int m=(l+r)>>1;
       if(idx<=m) setv(p<<1,l,m,idx,v);
       else setv(p<<1|1,m+1,r,idx,v);
       t[p]=max(t[p<<1],t[p<<1|1]);
   }
   void setv(int idx,int v){ setv(1,0,N-1,idx,v); }
   int mx() const{ return t[1]; }
};

void solve(){
   int n; if(!(cin>>n)) return;
   vi a(n); rep(i,n) cin>>a[i];
   Seg seg; seg.init(n+2);
   vi ans(n);
   rep(i,n){
       int x=a[i];
       if(x>0) seg.add(0,x-1,1);
       seg.setv(x,0);
       ans[i]=seg.mx();
   }
   rep(i,n){ if(i) cout<<' '; cout<<ans[i]; }
   cout<<'\n';
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