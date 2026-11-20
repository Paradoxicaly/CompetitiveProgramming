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
void solve(){
    int n; cin>>n;
    vi w(n+1),ti(n+1),to(n+1),o;
    rng(i,1,n+1) cin>>w[i];
    vector<vi> g(n+1);
    rep(i,n-1){ int u,v; cin>>u>>v; g[u].pb(v); g[v].pb(u); }
    vi st={1},par(n+1,0),it(n+1,0);
    ti[1]=0; o.pb(1);
    while(!st.empty()){
        int u=st.back();
        if(it[u]<sz(g[u])){
            int v=g[u][it[u]++];
            if(v==par[u]) continue;
            par[v]=u; ti[v]=sz(o); o.pb(v); st.pb(v);
        }else{ to[u]=sz(o)-1; st.pop_back(); }
    }
    vi pf(n+1,0),sf(n+2,0);
    rep(i,n) pf[i+1]=max(pf[i],w[o[i]]);
    for(int i=n-1;i>=0;--i) sf[i]=max(sf[i+1],w[o[i]]);
    int r=0;
    rng(u,1,n+1) if(max(pf[ti[u]],sf[to[u]+1])>w[u]&&(!r||w[u]>w[r])) r=u;
    print(r);
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
