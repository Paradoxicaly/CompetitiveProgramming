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
    const ll P=998244353;
    int n; cin>>n;
    vi a(n-1);
    for(auto&x:a) cin>>x;
    int L=-1,R=-1;
    rep(i,n-1) if(a[i]==n-1){ if(L<0) L=i; R=i; }
    if(L<0||*max_element(all(a))!=n-1){ print(0); return; }
    auto f=[&](int k)->ll{
        vi rc(n+1,0),cb(n+1,0);
        rep(i,k){
            if(i&&a[i]<a[i-1]) return 0;
            if(!i||a[i]>a[i-1]){ if(rc[a[i]]) return 0; rc[a[i]]=1; } else cb[a[i]]++;
        }
        for(int i=n-2;i>=k;--i){
            if(i<n-2&&a[i]<a[i+1]) return 0;
            if(i==n-2||a[i]>a[i+1]){ if(rc[a[i]]) return 0; rc[a[i]]=1; } else cb[a[i]]++;
        }
        ll r=1; int u=0,lt=0;
        rng(c,1,n){
            rep(t,cb[c]){ ll av=(c-1)-lt-u; if(av<=0) return 0; r=r*av%P; u++; }
            lt+=rc[c];
        }
        return r;
    };
    ll r=f(L);
    if(R+1!=L) r+=f(R+1);
    print(r%P);
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
