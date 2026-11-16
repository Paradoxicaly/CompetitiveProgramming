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
    vector<ll> a(n+1);
    rng(i,1,n+1) cin>>a[i];
    vector<vi> g(n+1);
    rep(i,n-1){ int u,v; cin>>u>>v; g[u].pb(v); g[v].pb(u); }
    vi par(n+1,0),d(n+1,0),ord={1},nx(n+1,0),ht(n+1);
    par[1]=-1;
    rep(i,n) for(int v:g[ord[i]]) if(v!=par[ord[i]]){ par[v]=ord[i]; d[v]=d[ord[i]]+1; ord.pb(v); }
    vector<ll> S(n+1),W(n+1),ans(n+1);
    for(int i=n-1;i>=0;--i){
        int x=ord[i];
        S[x]+=a[x]; W[x]+=a[x]*d[x]; chmax(ht[x],d[x]);
        if(par[x]>0){ S[par[x]]+=S[x]; W[par[x]]+=W[x]; chmax(ht[par[x]],ht[x]); }
    }
    rng(x,1,n+1){
        int c=0,w=0;
        for(int v:g[x]) if(v!=par[x]&&ht[v]==ht[x]){ c++; w=v; }
        if(c==1) nx[x]=w;
    }
    for(int x:ord){
        if(par[x]>0&&nx[par[x]]==x) continue;
        vi p;
        for(int y=x;y;y=nx[y]) p.pb(y);
        int m=sz(p);
        ll H=ht[x];
        vector<ll> A(m,0),B(m,0),M(m);
        rep(j,m){
            int y=p[j]; M[j]=d[y];
            for(int v:g[y]) if(v!=par[y]&&v!=nx[y]){ chmax(A[j],S[v]*(H-d[y])); chmax(M[j],(ll)ht[v]); }
        }
        rep(j,m){
            ll h=M[j]-d[p[j]];
            for(int i=j+1;i<m&&i<=j+h;++i) chmax(B[j],S[p[i]]*(M[j]-d[p[i]]+1));
        }
        ll bst=0;
        for(int s=m-1;s>=0;--s){
            chmax(bst,max(A[s],B[s]));
            int r=p[s];
            ans[r]=W[r]-(ll)d[r]*S[r]+bst;
        }
    }
    rng(i,1,n+1) cout<<ans[i]<<" \n"[i==n];
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
