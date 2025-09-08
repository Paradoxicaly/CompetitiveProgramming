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
 
struct Seg {
   int N; vector<int> t;
   void init(int n,int infv){
       N=1; while(N<n+2) N<<=1;
       t.assign(2*N, infv);
   }
   void upd(int p,int v){
       p+=N;
       if(v<t[p]) t[p]=v;
       p>>=1;
       while(p){
           int nv = std::min(t[p<<1], t[p<<1|1]);
           if(nv==t[p]) break;
           t[p]=nv; p>>=1;
       }
   }
   int qry(int l,int r){
       if(l>r) return (int)1e9;
       l+=N; r+=N;
       int res=(int)1e9;
       while(l<=r){
           if(l&1) res=min(res,t[l++]);
           if(!(r&1)) res=min(res,t[r--]);
           l>>=1; r>>=1;
       }
       return res;
   }
};
 
void solve(){
   int n,q; input(n,q);
   vi a(n+1); rng(i,1,n+1) cin>>a[i];
   vi L(n+1,0), R(n+1,n+1);
   {
       vector<int> st;
       rng(j,1,n+1){
           while(!st.empty() && a[st.back()]<=a[j]) st.pop_back();
           L[j]=st.empty()?0:st.back();
           st.pb(j);
       }
   }
   {
       vector<int> st;
       for(int j=n;j>=1;--j){
           while(!st.empty() && a[st.back()]>=a[j]) st.pop_back();
           R[j]=st.empty()?n+1:st.back();
           st.pb(j);
       }
   }
   vector<vector<pair<int,int>>> byL(n+2);
   rng(j,1,n+1){
       if(L[j]>=1) byL[L[j]].pb({j,R[j]});
   }
   vector<vector<pair<int,int>>> qs(n+2);
   vector<string> ans(q);
   rep(i,q){
       int l,r; input(l,r);
       if(r-l+1<3){ ans[i]="YES"; }
       else qs[l].pb({r,i});
   }
   Seg seg; seg.init(n, (int)1e9);
   for(int l=n;l>=1;--l){
       for(auto &pr: byL[l]) seg.upd(pr.fi, pr.se);
       for(auto &qr: qs[l]){
           int r=qr.fi, id=qr.se;
           int mn=seg.qry(l+1, r-1);
           ans[id]=(mn<=r)?"NO":"YES";
       }
   }
   rep(i,q) cout<<ans[i]<<(i+1<q?'\n':'\n');
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
