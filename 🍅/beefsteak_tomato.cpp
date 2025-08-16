/*
Tomato_Cultivator 
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using vi  = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

const int MOD = 1e9 + 7;

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, const vector<T> &vec) {
    o << "{"; for (int i = 0; i < (int)vec.size(); ++i) o << (i ? " " : "") << vec[i]; return o << "}";
}
template <typename A, typename B>
ostream& operator<<(ostream &o, const pair<A,B> &p){ return o << "(" << p.first << "," << p.second << ")"; }
template <typename... A>
void bug__(int c, A... a) {
    cerr << "\e[1;" << c << "m";
    ((cerr << a << ' '), ...);
    cerr << "\e[0m\n";
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
constexpr auto min(T... a){ return std::min({a...}); }
template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print(){ cout << '\n'; }

template<class T> bool chmin(T& a, const T& b){ if (b < a){ a = b; return true; } return false; }
template<class T> bool chmax(T& a, const T& b){ if (a < b){ a = b; return true; } return false; }

ll gcdll(ll a, ll b){ return b ? gcdll(b, a % b) : a; }
ll power(ll a, ll b, ll mod = MOD){
    ll res = 1 % mod;
    while (b){
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

mt19937 rng32((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
template<class T> T rnd(T l, T r){ return uniform_int_distribution<T>(l, r)(rng32); }

template<class F> struct y_combinator{
    F f; template<class... A> decltype(auto) operator()(A&&... a) const { return f(*this, std::forward<A>(a)...); }
};
template<class F> y_combinator<F> yfix(F f){ return {f}; }

struct DSU{
    vector<int> p, r;
    DSU(int n=0){ init(n); }
    void init(int n){ p.resize(n); r.assign(n,0); iota(all(p),0); }
    int find(int x){ while(x!=p[x]) x=p[x]=p[p[x]]; return x; }
    bool unite(int a,int b){
        a=find(a); b=find(b); if(a==b) return false;
        if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) ++r[a]; return true;
    }
};

template<class T>
struct Fenwick{
    int n; vector<T> f;
    Fenwick(int n=0){ init(n); }
    void init(int n_){ n=n_; f.assign(n+1,T()); }
    void add(int i, T v){ for(; i<=n; i+=i&-i) f[i]+=v; }
    T sumPrefix(int i) const { T r=T(); for(; i>0; i-=i&-i) r+=f[i]; return r; }
    T sumRange(int l,int r) const { return sumPrefix(r)-sumPrefix(l-1); }
    int kth(long long k){ int i=0; long long s=0; int p=1; while((p<<1)<=n) p<<=1; for(; p; p>>=1){ if(i+p<=n && s+f[i+p]<k){ i+=p; s+=f[i]; } } return i+1; }
};

template<class T>
struct SegTree{
    int n; vector<T> st;
    SegTree(int n=0){ init(n); }
    void init(int n_){ n=1; while(n<n_) n<<=1; st.assign(2*n, T()); }
    void setval(int p, T v){ for(st[p+=n]=v, p>>=1; p; p>>=1) st[p]=st[p<<1]+st[p<<1|1]; }
    void add(int p, T v){ for(p+=n, st[p]+=v, p>>=1; p; p>>=1) st[p]=st[p<<1]+st[p<<1|1]; }
    T query(int l,int r){ T L=T(), R=T(); l+=n; r+=n; while(l<r){ if(l&1) L=L+st[l++]; if(r&1) R=st[--r]+R; l>>=1; r>>=1; } return L+R; }
};

struct mint{
    static const int MODV = 998244353; //1e9+7
    int v;
    mint(): v(0) {}
    mint(long long x){ x%=MODV; if(x<0) x+=MODV; v=(int)x; }
    mint& operator+=(const mint& o){ v+=o.v; if(v>=MODV) v-=MODV; return *this; }
    mint& operator-=(const mint& o){ v-=o.v; if(v<0) v+=MODV; return *this; }
    mint& operator*=(const mint& o){ v=(int)((long long)v*o.v%MODV); return *this; }
    friend mint operator+(mint a, const mint& b){ return a+=b; }
    friend mint operator-(mint a, const mint& b){ return a-=b; }
    friend mint operator*(mint a, const mint& b){ return a*=b; }
    static mint pow(mint a, long long e){ mint r=1; for(; e; e>>=1, a*=a) if(e&1) r*=a; return r; }
    static mint inv(mint a){ return pow(a, MODV-2); }
    mint& operator/=(const mint& o){ return (*this) *= inv(o); }
    friend mint operator/(mint a, const mint& b){ return a/=b; }
};

template<class T>
struct Compressor{
    vector<T> v;
    void add(const T& x){ v.pb(x); }
    void build(){ sort(all(v)); v.erase(unique(all(v)), v.end()); }
    int get(const T& x) const { return (int)(lower_bound(all(v), x)-v.begin()); }
    int size() const { return (int)v.size(); }
};

struct PairHash{
    size_t operator()(const pii& p) const noexcept {
        return (uint64_t(p.first)<<32) ^ uint64_t(p.second);
    }
};

void solve(){
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef MULTI_TEST
    int T; if(!(cin >> T)) return 0;
    while(T--) solve();
#else
    solve();
#endif
    return 0;
}