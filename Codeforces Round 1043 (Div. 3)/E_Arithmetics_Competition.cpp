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

void solve(){
    int n,m,q; input(n,m,q);
    vector<ll>a(n+1),b(m+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int j=1;j<=m;j++) cin>>b[j];
    sort(a.begin()+1,a.end(),greater<ll>());
    sort(b.begin()+1,b.end(),greater<ll>());
    vector<ll>A(n+1),B(m+1);
    for(int i=1;i<=n;i++) A[i]=A[i-1]+a[i];
    for(int j=1;j<=m;j++) B[j]=B[j-1]+b[j];

    auto geta=[&](int i)->ll{ return (1<=i && i<=n)?a[i]:0LL; };
    auto getb=[&](int j)->ll{ return (1<=j && j<=m)?b[j]:0LL; };

    while(q--){
        int x,y,z; input(x,y,z);
        int L=max(0,z-y), R=min(z,x);
        int lo=0,hi=z;
        auto ok=[&](int t)->bool{
            if(t==0) return true;
            return geta(t) >= getb(z - t + 1);
        };
        while(lo<hi){
            int mid=(lo+hi+1)>>1;
            if(ok(mid)) lo=mid;
            else hi=mid-1;
        }
        int t0=lo;
        int t=t0;
        if(t<L) t=L;
        if(t>R) t=R;
        ll ans=A[min(t,n)] + B[min(z-t,m)];
        print(ans);
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