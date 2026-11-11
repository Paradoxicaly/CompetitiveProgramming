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
    const int N=200005;
    static vi sp,cnt;
    if(sp.empty()){
        sp.assign(N,0);cnt.assign(N,0);
        for(int i=2;i<N;i++)if(!sp[i])for(int j=i;j<N;j+=i)if(!sp[j])sp[j]=i;
    }
    auto pf=[&](int x){vi r;while(x>1){int p=sp[x];r.pb(p);while(x%p==0)x/=p;}return r;};
    int n;cin>>n;
    vi a(n);vector<ll>b(n);
    for(auto&x:a)cin>>x;
    for(auto&x:b)cin>>x;
    vector<vi>P(n);vi T;
    bool z=0;
    for(int i=0;i<n;i++){
        P[i]=pf(a[i]);
        for(int p:P[i]){if(++cnt[p]>=2)z=1;T.pb(p);}
    }
    ll ans=0;
    if(!z){
        vector<ll>c(n);
        for(int i=0;i<n;i++)c[i]=a[i]%2?b[i]:0;
        sort(all(c));
        ans=c[0]+c[1];
        for(int i=0;i<n;i++)for(int p:pf(a[i]+1))if(cnt[p])chmin(ans,b[i]);
        int m=min_element(all(b))-b.begin();
        for(int p:P[m])cnt[p]--;
        for(int p:T)if(cnt[p])chmin(ans,b[m]*((p-a[m]%p)%p));
        for(int p:P[m])cnt[p]++;
    }
    for(int p:T)cnt[p]=0;
    cout<<ans<<"\n";
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
