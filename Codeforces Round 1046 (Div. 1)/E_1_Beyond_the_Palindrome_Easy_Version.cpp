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

static vector<int> FAC, IFAC, W;

int nCr(int n, int r){
    if(r < 0 || r > n) return 0;
    return (int)((ll)FAC[n] * IFAC[r] % MOD * IFAC[n-r] % MOD);
}

void build_all(int LIM){
    FAC.assign(LIM+1, 1);
    for(int i=1;i<=LIM;i++) FAC[i] = (ll)FAC[i-1] * i % MOD;
    IFAC.assign(LIM+1, 1);
    IFAC[LIM] = (int)power(FAC[LIM], MOD-2);
    for(int i=LIM;i>=1;i--) IFAC[i-1] = (ll)IFAC[i] * i % MOD;

    int LIMF = LIM + 1;
    vector<int> sig(LIMF+1, 0);
    for(int d=1; d<=LIMF; ++d)
        for(int m=d; m<=LIMF; m+=d){
            int v = sig[m] + d;
            if(v >= MOD) v -= MOD;
            sig[m] = v;
        }

    int maxK = 0; for(int t=LIMF; t>0; t>>=1) ++maxK;
    vector<int> pow2(maxK+2,1);
    for(int k=1;k<=maxK+1;k++) pow2[k] = (pow2[k-1] << 1) % MOD;

    vector<int> f(LIMF+1, 0);
    for(int i=1;i<=LIMF;i++){
        int x = i, c = 0;
        while((x & 1) == 0){ x >>= 1; ++c; }
        f[i] = (ll)pow2[c+1] * sig[x] % MOD;
    }

    vector<long long> acc(LIM+3, 0);
    for(int i=1;i<=LIMF;i++){
        if(i-1 <= LIM) acc[i-1] += f[i];
        if(i   <= LIM) acc[i]   -= 2LL * f[i];
        if(i+1 <= LIM) acc[i+1] += f[i];
    }
    acc[0] -= 1;

    W.assign(LIM+1, 0);
    long long v0 = acc[0] % MOD; if(v0 < 0) v0 += MOD;
    W[0] = (int)v0;
    for(int i=1;i<=LIM;i++){
        long long v = acc[i] + ((i & 1) ? 2LL : -2LL);
        v %= MOD;
        if(v < 0) v += MOD;
        W[i] = (int)v;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if(!(cin >> T)) return 0;
    vector<int> qs(T);
    int maxN = 0;
    for(int i=0;i<T;i++){
        cin >> qs[i];
        if(qs[i] > maxN) maxN = qs[i];
    }

    build_all(maxN);

    for(int n : qs){
        ll ans = 0;
        for(int d = (n & 1); d <= n; d += 2){
            int ones = (n + d) >> 1;
            ans += (ll)nCr(n, ones) * W[d] % MOD;
            if(ans >= MOD) ans -= MOD;
        }
        print((int)ans);
    }
    return 0;
}