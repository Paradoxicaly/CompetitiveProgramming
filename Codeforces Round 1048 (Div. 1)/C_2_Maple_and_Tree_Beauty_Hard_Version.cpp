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
   int n,k; input(n,k);
   vector<vi> g(n+1);
   for(int i=2;i<=n;i++){ int p; cin>>p; g[p].pb(i); }
   vector<int> dep(n+1,0);
   queue<int> q; q.push(1); dep[1]=1;
   while(!q.empty()){
       int v=q.front(); q.pop();
       for(int u: g[v]){ dep[u]=dep[v]+1; q.push(u); }
   }
   int mx=*max_element(dep.begin()+1,dep.end());
   vector<int> level(mx+2,0);
   for(int i=1;i<=n;i++) level[dep[i]]++;
   int D=INT_MAX;
   for(int i=1;i<=n;i++) if(g[i].empty()) D=min(D,dep[i]);
   vector<int> a; a.reserve(D);
   for(int d=1; d<=D; d++) a.pb(level[d]);
   vector<int> pref(D+1,0);
   for(int i=0;i<D;i++) pref[i+1]=pref[i]+a[i];
   int ones=n-k;
 
   struct DynBitset{
       int W; vector<unsigned long long> b;
       DynBitset(int n=0){init(n);}
       void init(int n){ W=(n>>6)+1; b.assign(W,0); b[0]=1ULL; }
       void or_shift(int s){
           if(s<=0) return;
           int ws=s>>6, bs=s&63;
           vector<unsigned long long> old=b;
           for(int i=W-1;i>=0;--i){
               unsigned long long v=0;
               int j=i-ws;
               if(j>=0){
                   v = old[j]<<bs;
                   if(bs && j-1>=0) v |= (old[j-1]>>(64-bs));
               }
               b[i] |= v;
           }
       }
       bool get(int pos) const{ return (b[pos>>6]>>(pos&63))&1ULL; }
   };
 
   auto feasible = [&](int L)->bool{
       if(L==0) return true;
       int sum=pref[L];
       int lo=max(0,sum-ones);
       int hi=min(k,sum);
       if(lo>hi) return false;
       int B=hi;
       DynBitset dp(B);
       vector<int> freq(n+1,0), used; used.reserve(L);
       for(int i=0;i<L;i++){ int v=a[i]; if(!freq[v]) used.pb(v); freq[v]++; }
       vector<int> weights; weights.reserve(L);
       for(int v: used){
           int c=freq[v], p=1;
           while(c){
               int take=min(p,c);
               long long w=1LL*v*take;
               if(w<=B) weights.pb((int)w);
               c-=take; p<<=1;
           }
       }
       for(int w: weights) dp.or_shift(w);
       for(int s=lo;s<=hi;s++) if(dp.get(s)) return true;
       return false;
   };
 
   int lo=0,hi=D,ans=0;
   while(lo<=hi){
       int mid=(lo+hi)>>1;
       if(feasible(mid)){ ans=mid; lo=mid+1; }
       else hi=mid-1;
   }
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