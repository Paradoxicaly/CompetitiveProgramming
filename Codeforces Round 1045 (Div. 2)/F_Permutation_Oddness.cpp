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

static const int N=800;
ll jc[2005],invf[2005];
ll fdp[2][N+5][N+5],resv[N*2+5];
int a4[4];

inline void addmod(ll& x,ll y){ x+=y; if(x>=MOD) x-=MOD; }
inline ll C(int n,int k){ if(n<0||k<0||k>n) return 0; return jc[n]*invf[k]%MOD*invf[n-k]%MOD; }

void go(int x,int y,int z){
    for(int i=0;i<=a4[0]+a4[2];++i) if(fdp[0][x][i]) for(int j=0;j<=a4[1]+a4[3];++j) if(fdp[1][y][j]){
        resv[(i+j)*2+x+y-1]=(resv[(i+j)*2+x+y-1]+fdp[0][x][i]*fdp[1][y][j]%MOD*z)%MOD;
    }
}

void solve(){
   int T; if(!(cin>>T)) return;
   jc[0]=1; invf[0]=1;
   for(int i=1;i<=2000;++i) jc[i]=jc[i-1]*i%MOD;
   invf[2000]=337096023;
   for(int i=1999;i>=1;--i) invf[i]=invf[i+1]*(i+1)%MOD;
   while(T--){
       int n=0;
       for(int i=0;i<4;++i){ cin>>a4[i]; n+=a4[i]; }
       for(int T2=0;T2<=1;++T2){
           for(int i=0;i<=n+1;++i) for(int j=0;j<=n+1;++j) fdp[T2][i][j]=0;
           int x=a4[0],y=a4[2];
           for(int i=2;i<=x+y;++i){
               int x1=(i-2)/2,y1=(i-2)-x1;
               ll t1=(C(x-1,y1)*C(y-1,x1)+C(x-1,x1)*C(y-1,y1))%MOD;
               if(!t1) continue;
               x1=i-1; y1=x+y-1-x1;
               for(int j=0;j<=x1;++j) for(int k=0;k<=y1;++k){
                   addmod(fdp[T2][j+k+1][x1-j], t1*C(x1,j)%MOD*C(y1,k)%MOD);
               }
           }
           swap(a4[0],a4[1]); swap(a4[2],a4[3]);
       }
       memset(resv,0,sizeof(resv));
       for(int i=1;i<=n/2+1;++i){ go(i,i,2); go(i,i+1,1); go(i+1,i,1); }
       for(int i=0;i<=n*2-2;++i){ cout<<(resv[i]%MOD)<<(i==n*2-2?'\n':' '); }
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
