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
    ll S; int q; cin>>S>>q;
    vector<ll> d,e;
    for(ll i=1;i*i<=S;++i) if(S%i==0){ d.pb(i); if(i!=S/i) e.pb(S/i); }
    d.insert(d.end(),e.rbegin(),e.rend());
    int k=sz(d);
    vector<ll> P(k+1,0);
    rep(i,k) P[i+1]=P[i]+(d[i]-(i?d[i-1]:0))*(S/d[i]);
    auto F=[&](ll c)->ll{
        int i=lower_bound(all(d),c)-d.begin();
        return P[i]+(c-(i?d[i-1]:0))*(S/d[i]);
    };
    while(q--){
        ll x,y; cin>>x>>y;
        int lo=0,hi=k;
        while(lo<hi){ int m=(lo+hi)/2; if(S/d[m]>y) lo=m+1; else hi=m; }
        ll p=lo?d[lo-1]:0;
        ll r=y*min(x,p);
        if(x>p) r+=F(min(x,S))-F(p);
        print(r);
    }
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
