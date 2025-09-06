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
   int n; cin>>n;
   vi vals(n+1), sorted(n+1);
   unordered_map<int, vector<int>> locs;
   vi done(n+2,0);

   for(int i=1;i<=n;i++){
       cin>>vals[i];
       sorted[i]=vals[i];
       locs[vals[i]].pb(i);
   }

   sort(sorted.begin()+1,sorted.begin()+n+1,greater<int>());

   priority_queue<pii> active; 
   int clones=0;

   for(int step=1; step<=n; step++){
       while(!active.empty() && done[active.top().se]) active.pop();

       if(active.empty() || active.top().fi!=sorted[step]){
           auto &vec = locs[sorted[step]];
           while(!vec.empty() && done[vec.back()]) vec.pop_back();
           int pos = vec.back(); vec.pop_back();
           active.push({sorted[step],pos});
           clones++;
       }

       auto top = active.top(); active.pop();
       int pos = top.se;
       done[pos]=1;

       if(pos>1 && !done[pos-1]) active.push({vals[pos-1],pos-1});
       if(pos<n && !done[pos+1]) active.push({vals[pos+1],pos+1});
   }

   print(clones);
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