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

const int MOD = 998244353;

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

const int LIM = 20000010;

static int PR[LIM], PCNT;
static int F[LIM], G_[LIM];
static int FAC[LIM], IFAC[LIM];

int modexp(int b, int e){
    int r=1;
    while(e){
        if(e&1) r=(ll)r*b%MOD;
        b=(ll)b*b%MOD;
        e>>=1;
    }
    return r;
}

void preprocess(int n){
    F[1]=1;
    for(int i=2;i<=n;i++){
        if(!F[i]){
            PR[++PCNT]=i;
            F[i]=G_[i]=i + (i>2);
        }
        for(int j=1;j<=PCNT;j++){
            int p=PR[j];
            long long ip=1LL*i*p;
            if(ip>n) break;
            if(i%p==0){
                G_[ip] = (int)((long long)G_[i]*p + (j>1));
                F[ip] = (int)((long long)F[i]/G_[i]*G_[ip]);
                break;
            }
            F[ip] = (int)((long long)F[i] * (p + (j>1)));
            G_[ip] = p + (j>1);
        }
    }
    FAC[0]=1;
    for(int i=1;i<=n;i++) FAC[i]=(ll)FAC[i-1]*i%MOD;
    IFAC[n]=modexp(FAC[n], MOD-2);
    for(int i=n;i>=1;i--) IFAC[i-1]=(ll)IFAC[i]*i%MOD;
}

void solve(){
    static bool inited=false;
    if(!inited){ preprocess(20000001); inited=true; }
    int n; cin>>n;
    int res=0;
    for(int i=0;i<=n;i++){
        int coef = (ll)IFAC[i]*IFAC[n-i]%MOD;
        int a = n - 2*i - 1; if(a<0) a=-a;
        int b = n - 2*i;     if(b<0) b=-b;
        int diff = F[a]; diff -= F[b]; if(diff<0) diff+=MOD;
        res += (ll)coef * diff % MOD; if(res>=MOD) res-=MOD;
    }
    res = (ll)res * FAC[n] % MOD;
    res = (res + res) % MOD;
    int twon = (int)power(2, n);
    if(n&1){ res += twon; if(res>=MOD) res-=MOD; }
    else { res -= twon; if(res<0) res+=MOD; }
    print(res);
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