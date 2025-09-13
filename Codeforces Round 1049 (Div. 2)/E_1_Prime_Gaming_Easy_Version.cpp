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
   int n,m; input(n,m);
   int k; input(k);
   vi c(k); rep(i,k) input(c[i]);
   if(m==1){ print(1); return; }
   vector<vector<unsigned char>> dpA(n+1), dpB(n+1);
   dpA[1].assign(2,0); dpB[1].assign(2,0);
   dpA[1][0]=0; dpA[1][1]=1; dpB[1][0]=0; dpB[1][1]=1;
   vector<vi> G(n+1);
   rng(p,1,n+1){
      for(int x: c) if(x<=p) G[p].pb(x);
   }
   rng(p,2,n+1){
      int M=1<<p;
      dpA[p].assign(M,0);
      dpB[p].assign(M,1);
      rep(mask,M){
         unsigned char valA=0;
         for(int idx: G[p]){
            int i=idx-1;
            int low = mask & ((1<<i)-1);
            int high = (mask>> (i+1));
            int nm = low | (high<<i);
            if(dpB[p-1][nm]){ valA=1; break; }
         }
         dpA[p][mask]=valA;
         unsigned char valB=1;
         for(int idx: G[p]){
            int i=idx-1;
            int low = mask & ((1<<i)-1);
            int high = (mask>> (i+1));
            int nm = low | (high<<i);
            if(!dpA[p-1][nm]){ valB=0; break; }
         }
         dpB[p][mask]=valB;
      }
   }
   int M = 1<<n;
   long long win=0;
   rep(mask,M) if(dpA[n][mask]) ++win;
   long long ans = ((1LL<<n) + win) % MOD;
   print(ans);
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