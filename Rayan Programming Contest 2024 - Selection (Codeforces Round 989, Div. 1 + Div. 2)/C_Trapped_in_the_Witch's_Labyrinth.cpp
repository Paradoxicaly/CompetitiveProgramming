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
   int n,m; input(n,m);
   vector<string> g(n);
   rep(i,n) input(g[i]);
   int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
   string ds="UDLR";
   vector<vi> c(n,vi(m)),e(n,vi(m));
   queue<pii> q;
   auto in=[&](int x,int y){ return x>=0&&x<n&&y>=0&&y<m; };
   rep(i,n) rep(j,m){
      if(g[i][j]=='?'){
         rep(d,4) if(!in(i+dx[d],j+dy[d])) c[i][j]++;
         if(c[i][j]==4){ e[i][j]=1; q.push({i,j}); }
      }
      else{
         int d=ds.find(g[i][j]);
         if(!in(i+dx[d],j+dy[d])){ e[i][j]=1; q.push({i,j}); }
      }
   }
   int cnt=0;
   while(!q.empty()){
      auto [x,y]=q.front(); q.pop(); cnt++;
      rep(d,4){
         int a=x+dx[d],b=y+dy[d];
         if(!in(a,b)||e[a][b]) continue;
         if(g[a][b]=='?'){ if(++c[a][b]==4){ e[a][b]=1; q.push({a,b}); } }
         else{
            int t=ds.find(g[a][b]);
            if(a+dx[t]==x&&b+dy[t]==y){ e[a][b]=1; q.push({a,b}); }
         }
      }
   }
   print(n*m-cnt);
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
