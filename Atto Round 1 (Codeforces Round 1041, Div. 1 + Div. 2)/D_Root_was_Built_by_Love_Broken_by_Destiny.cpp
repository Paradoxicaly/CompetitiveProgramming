/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
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
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
constexpr auto min(T... a){
    return std::min({a...});
}

template<class... T>
constexpr auto max(T... a){
    return std::max({a...});
}

template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

ll gcd(ll a, ll b) { 
    return b ? gcd(b, a % b) : a; 
}

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int mul(ll a, ll b) { return int((a*b) % MOD); }

const int MAXN = 200000;
static vector<int> fact(MAXN+5);

void solve() {
    int n,m; input(n,m);
    vector<vi> adj(n+1);
    rep(i,m){ int u,v; input(u,v); adj[u].pb(v); adj[v].pb(u); }
    if(m != n-1){ print(0); return; }
    vi deg(n+1);
    rng(i,1,n+1) deg[i] = sz(adj[i]);
    vi S;
    rng(i,1,n+1) if(deg[i]>=2) S.pb(i);
    if(S.empty()){ print(2); return; }
    vi nonLeafNbr(n+1,0);
    bool ok=true;
    rng(u,1,n+1){
        for(int v: adj[u]) if(deg[v]>=2) nonLeafNbr[u]++;
        if(nonLeafNbr[u] >= 3){ ok=false; break; }
    }
    if(!ok){ print(0); return; }
    int k = sz(S);
    vi vis(n+1,0);
    queue<int> q;
    q.push(S[0]); vis[S[0]]=1;
    int cnt=0;
    while(!q.empty()){
        int u=q.front(); q.pop(); cnt++;
        for(int v: adj[u]) if(deg[v]>=2 && !vis[v]){ vis[v]=1; q.push(v); }
    }
    if(cnt != k){ print(0); return; }
    if(k==1){
        int leaves = n-1;
        int ans = mul(2, fact[leaves]);
        print(ans);
        return;
    }
    ll ans = 4;
    for(int u: S){
        int leaves = deg[u] - nonLeafNbr[u];
        ans = (ans * fact[leaves]) % MOD;
    }
    print(int(ans));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fact[0]=1;
    rng(i,1,MAXN+1) fact[i]=mul(fact[i-1], i);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
