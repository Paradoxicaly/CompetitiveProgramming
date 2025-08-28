/*
Tomato_Cultivator
*/
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using pii = pair<int,int>;
using vi  = vector<int>;

#define pb  push_back
#define fi  first
#define se  second
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

ll power(ll a, long long b, ll m = MOD){
    ll res = 1 % m;
    a %= m;
    while(b > 0){
        if(b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

struct UF {
    vi p, rk;
    UF(int n=0){ init(n); }
    void init(int n){ p.resize(n+1); rk.assign(n+1,0); iota(all(p),0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool join(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(rk[a]<rk[b]) swap(a,b);
        p[b]=a; if(rk[a]==rk[b]) rk[a]++;
        return true;
    }
};

void solve(){
    int n,m; ll Vlim; 
    input(n,m,Vlim);
    vector<ll> w(n+1);
    rep(i,n){ cin>>w[i+1]; }
    vector<pii> E(m);
    vector<vector<pair<int,int>>> g(n+1);
    rep(i,m){
        int u,v; input(u,v);
        E[i]={u,v};
        g[u].pb({v,i});
        g[v].pb({u,i});
    }
    vi tin(n+1,0), low(n+1,0);
    int timer = 0;
    vector<int> estk;
    vector<vector<int>> comps;
    auto push_comp = [&](int until_id){
        vector<int> comp;
        while(true){
            int e = estk.back(); estk.pop_back();
            comp.pb(e);
            if(e==until_id) break;
        }
        comps.pb(move(comp));
    };
    function<void(int,int)> dfs = [&](int u,int pe){
        tin[u]=low[u]=++timer;
        for(auto [v,id]: g[u]){
            if(!tin[v]){
                estk.pb(id);
                dfs(v,id);
                chmin(low[u], low[v]);
                if(low[v] >= tin[u]) push_comp(id);
            }else if(id!=pe && tin[v] < tin[u]){
                estk.pb(id);
                chmin(low[u], tin[v]);
            }
        }
    };
    rng(s,1,n+1) if(!tin[s]) dfs(s,-1);
    UF uf(n);
    vector<char> mustZero(n+1, 0);
    vector<char> inEq(n+1, 0);
    for(const auto& compEdges : comps){
        if(sz(compEdges) <= 1) continue;
        vector<int> nodes; nodes.reserve(2*sz(compEdges));
        for(int id: compEdges){
            nodes.pb(E[id].fi); nodes.pb(E[id].se);
        }
        sort(all(nodes)); nodes.erase(unique(all(nodes)), nodes.end());
        int k = sz(nodes);
        unordered_map<int,int> idx; idx.reserve(2*k);
        rep(i,k) idx[nodes[i]] = i;
        vector<vi> h(k);
        for(int id: compEdges){
            int a = idx[E[id].fi], b = idx[E[id].se];
            h[a].pb(b); h[b].pb(a);
        }
        vi color(k, -1);
        bool bip = true;
        rep(i,k) if(color[i]==-1){
            queue<int> q; color[i]=0; q.push(i);
            while(!q.empty() && bip){
                int x=q.front(); q.pop();
                for(int y: h[x]){
                    if(color[y]==-1){ color[y]=color[x]^1; q.push(y); }
                    else if(color[y]==color[x]){ bip=false; break; }
                }
            }
            if(!bip) break;
        }
        if(!bip){
            for(int v: nodes) mustZero[v]=1;
        }else{
            for(int i=1;i<k;i++) uf.join(nodes[0], nodes[i]);
            for(int v: nodes) inEq[v]=1;
        }
    }
    rng(v,1,n+1){
        if(mustZero[v] && w[v]!=-1 && w[v]!=0){
            print(0); return;
        }
    }
    unordered_map<int, vector<int>> part;
    part.reserve(n*2);
    rng(v,1,n+1) if(inEq[v]) part[uf.find(v)].pb(v);
    long long freeVars = 0;
    for(auto &kv : part){
        auto &lst = kv.second;
        ll fixed = -1;
        for(int v: lst){
            if(mustZero[v]){
                if(fixed==-1) fixed = 0;
                else if(fixed != 0){ print(0); return; }
            }
        }
        for(int v: lst){
            if(w[v] != -1){
                if(fixed==-1) fixed = w[v];
                else if(fixed != w[v]){ print(0); return; }
            }
        }
        if(fixed==-1) ++freeVars;
    }
    rng(v,1,n+1){
        if(inEq[v]) continue;
        if(mustZero[v]){
            if(w[v]!=-1 && w[v]!=0){ print(0); return; }
        }else{
            if(w[v]==-1) ++freeVars;
        }
    }
    print(power(Vlim, freeVars, MOD));
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

