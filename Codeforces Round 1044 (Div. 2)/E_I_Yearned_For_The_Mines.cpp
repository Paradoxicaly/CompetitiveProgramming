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
 
static inline void dump_ops(const vector<pii>& ops){
    cout<<sz(ops)<<"\n";
    for(auto &e:ops) cout<<e.fi<<" "<<e.se<<"\n";
}
 
void solve(){
    int n; cin>>n;
    vector<vector<int>> adj(n+1);
    rep(i,n-1){
        int a,b; cin>>a>>b;
        adj[a].pb(b); adj[b].pb(a);
    }
 
    auto path_strategy = [&](vector<pii>& out){
        vector<int> deg(n+1);
        for(int i=1;i<=n;i++) deg[i]=sz(adj[i]);
        int leaf=1; for(int i=1;i<=n;i++) if(deg[i]==1){ leaf=i; break; }
        int p=0,u=leaf;
        for(;;){
            out.pb({1,u});
            int nxt=0;
            for(int v:adj[u]) if(v!=p){ nxt=v; break; }
            if(!nxt) break;
            p=u; u=nxt;
        }
    };
 
    if(n==2){
        cout<<2<<"\n";
        cout<<1<<" "<<1<<"\n";
        cout<<1<<" "<<2<<"\n";
        return;
    }
    bool is_line=true;
    for(int i=1;i<=n;i++) if(sz(adj[i])>2){ is_line=false; break; }
    if(is_line){
        vector<pii> ops;
        path_strategy(ops);
        dump_ops(ops);
        return;
    }
 
    vector<int> parent(n+1,-1), order; order.pb(1);
    for(int i=0;i<sz(order);i++){
        int u=order[i];
        for(int v:adj[u]) if(v!=parent[u]) parent[v]=u, order.pb(v);
    }
    vector<vector<int>> child(n+1);
    for(int v=2;v<=n;v++) child[parent[v]].pb(v);
 
    vector<long long> f_free(n+1,0), f_keep1(n+1,0), f_keep2(n+1,0);
    for(int i=n-1;i>=0;i--){
        int u=order[i];
        long long sum_free=0;
        for(int v:child[u]) sum_free += max(f_free[v], f_keep2[v]);
        f_free[u]=sum_free;
        long long base=0,b1=0,b2=0;
        for(int v:child[u]){
            base += f_free[v];
            long long gain = f_keep1[v]-f_free[v];
            if(gain>b1){ b2=b1; b1=gain; }
            else if(gain>b2) b2=gain;
        }
        f_keep1[u] = 1 + base + max(0LL,b1);
        f_keep2[u] = 1 + base + max(0LL,b1) + max(0LL,b2);
    }
 
    vector<int> pick(n+1,0);
    function<void(int,int,int)> build = [&](int u,int from_parent,int take){
        pick[u]=take;
        if(!take){
            for(int v:child[u]){
                if(f_keep2[v]>=f_free[v]) build(v,0,1);
                else build(v,0,0);
            }
        }else{
            vector<pair<long long,int>> cand;
            for(int v:child[u]) cand.pb({f_keep1[v]-f_free[v],v});
            sort(cand.rbegin(),cand.rend());
            int need = from_parent?1:2, used=0;
            vector<int> chosen;
            for(auto &p:cand) if(p.fi>0 && used<need){ chosen.pb(p.se); used++; }
            int a = sz(chosen)>=1 ? chosen[0] : -1;
            int b = sz(chosen)>=2 ? chosen[1] : -1;
            for(int v:child[u]){
                if(v==a){ build(v,1,1); a=-1; }
                else if(v==b){ build(v,1,1); b=-1; }
                else build(v,1,0);
            }
        }
    };
    if(f_keep2[1]>=f_free[1]) build(1,0,1);
    else build(1,0,0);
 
    vector<int> stay, gone;
    for(int i=1;i<=n;i++) if(pick[i]) stay.pb(i); else gone.pb(i);
 
    vector<pii> ops;
    for(int v:gone){ ops.pb({1,v}); ops.pb({2,v}); }
 
    vector<int> deg(n+1,0), seen(n+1,0);
    for(int u=1;u<=n;u++) if(pick[u]) for(int v:adj[u]) if(pick[v]) deg[u]++;
 
    for(int u=1;u<=n;u++) if(pick[u] && deg[u]<=1 && !seen[u]){
        int p=0,x=u;
        for(;;){
            seen[x]=1; ops.pb({1,x});
            int nx=0;
            for(int y:adj[x]) if(pick[y] && y!=p){ nx=y; break; }
            if(!nx) break;
            p=x; x=nx;
        }
    }
 
    long long cap = (5LL*n)/4;
    if((long long)ops.size()>cap){
        vector<pii> alt;
        path_strategy(alt);
        ops.swap(alt);
    }
    dump_ops(ops);
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
