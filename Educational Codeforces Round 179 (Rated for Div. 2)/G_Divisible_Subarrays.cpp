/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)

const int INF = 1e9+7;
const ll LINF = 1e18;
const int MOD = 1e9+7;

#ifdef Tomato
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v){
    o<<"{"; int f=0;
    for(auto& x:v) o<<(f++?" ":"")<<x;
    return o<<"}";
}
#define bug(x...) do{cerr<<"\e[32m"; fprintf(stderr,x); cerr<<"\e[0m\n";}while(0)
#else
#define bug(...)
#endif

template<class... T>
constexpr auto min(T... a){ return std::min({a...}); }

template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }

template<class... T>
void input(T&... a){ (cin>>...>>a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout<<a;
    (cout<<...<<(cout<<' ',b));
    cout<<'\n';
}
void print(){ cout<<'\n'; }

ll gcd(ll a,ll b){ return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b){ return a/gcd(a,b)*b; }
ll power(ll a,ll b,ll m=MOD){
    ll r=1;
    while(b){ if(b&1) r=r*a%m; a=a*a%m; b>>=1; }
    return r;
}

struct Solver {
    int n;
    vector<int> p, nxtmx, nxtmn;
    vector<array<int,18>> up, mx;
    Solver(const vector<int>& a):p(a){
        n=sz(p);
        nxtmx.resize(n);
        vector<int> st;
        for(int i=n-1;i>=0;--i){
            while(!st.empty()&&p[st.back()]<p[i]) st.pop_back();
            nxtmx[i]=st.empty()?n:st.back();
            st.pb(i);
        }
        vector<vector<int>> qr(n+1);
        rep(i,n) qr[nxtmx[i]].pb(i);
        nxtmn.assign(n,n);
        st.clear();
        for(int i=n-1;i>=0;--i){
            while(!st.empty()&&p[st.back()]>p[i]) st.pop_back();
            st.pb(i);
            for(int j:qr[i]){
                int l=0,r=sz(st)-1;
                while(l<=r){
                    int m=(l+r)/2;
                    if(p[st[m]]<p[j]){
                        nxtmn[j]=st[m];
                        l=m+1;
                    } else r=m-1;
                }
            }
        }
        up.assign(n+1,{});
        mx.assign(n+1,{});
        rep(i,n){
            up[i][0]=nxtmx[i];
            mx[i][0]=nxtmn[i];
        }
        up[n][0]=n; mx[n][0]=0;
        rep(j,17) rep(i,n+1){
            up[i][j+1]=up[ up[i][j] ][j];
            mx[i][j+1]=max(mx[i][j], mx[ up[i][j] ][j]);
        }
    }
    bool query(int l,int r){
        int v=l;
        for(int j=17;j>=0;--j){
            if(up[v][j]>=r) continue;
            if(mx[v][j]>=r) return true;
            v=up[v][j];
        }
        return false;
    }
};

void solve(){
    int n; input(n);
    vector<vector<int>> P(2, vector<int>(n));
    rep(i,n){ cin>>P[0][i]; --P[0][i]; }
    P[1]=P[0];
    reverse(all(P[1]));
    Solver s0(P[0]), s1(P[1]);
    int m; cin>>m;
    rep(i,m){
        if(i%10==0) cout.flush();
        int l,r; input(l,r);
        --l; --r;
        bool ok = s0.query(l,r+1) || s1.query(n-1-r, n-l);
        cout<<(ok?"YES\n":"NO\n");
    }
    cout.flush();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}