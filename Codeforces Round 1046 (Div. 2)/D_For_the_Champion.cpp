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

static inline ll ping(char d,ll k){
    cout<<"? "<<d<<' '<<k<<'\n'<<flush;
    ll s; 
    if(!(cin>>s)) exit(0);
    if(s==-1) exit(0);
    return s;
}

void solve(){
   int n; input(n);
   vector<ll> x(n), y(n);
   rep(i,n) cin>>x[i]>>y[i];
   ll p = LLONG_MIN, q = LLONG_MIN;
   rep(i,n){
       p = max(p, x[i]+y[i]);
       q = max(q, x[i]-y[i]);
   }
   const ll K = 1000000000LL;
   ping('R',K);
   ping('R',K);
   ping('U',K);
   ll a = ping('U',K);
   ping('D',K);
   ping('D',K);
   ping('D',K);
   ll b = ping('D',K);
   ll s = a - 4LL*K + p;
   ll d = b - 4LL*K + q;
   ll X = (s + d) / 2;
   ll Y = (s - d) / 2;
   cout<<"! "<<X<<' '<<Y<<'\n'<<flush;
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