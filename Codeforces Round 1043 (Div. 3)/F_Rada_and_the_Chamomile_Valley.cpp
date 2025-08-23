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

void solve(){
    int n,m; input(n,m);
    vector<vector<pair<int,int>>> g(n+1);
    vector<pair<int,int>> edges(m+1);
    for(int i=1;i<=m;i++){
        int u,v; cin>>u>>v;
        edges[i]={u,v};
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }
    int q; input(q);
    vector<int> c(q); rep(i,q) cin>>c[i];

    vector<int> tin(n+1,-1), low(n+1,-1);
    vector<char> isB(m+1,0);
    int timer=0;
    function<void(int,int)> dfs=[&](int v,int pe){
        tin[v]=low[v]=++timer;
        for(auto [to,id]: g[v]){
            if(id==pe) continue;
            if(tin[to]==-1){
                dfs(to,id);
                low[v]=min(low[v],low[to]);
                if(low[to]>tin[v]) isB[id]=1;
            }else{
                low[v]=min(low[v],tin[to]);
            }
        }
    };
    dfs(1,-1);

    vector<int> comp(n+1,-1);
    int cid=0;
    function<void(int)> paint=[&](int s){
        stack<int> st; st.push(s); comp[s]=cid;
        while(!st.empty()){
            int v=st.top(); st.pop();
            for(auto [to,id]: g[v]){
                if(isB[id]) continue;
                if(comp[to]==-1){
                    comp[to]=cid;
                    st.push(to);
                }
            }
        }
    };
    for(int v=1;v<=n;v++) if(comp[v]==-1){ cid++; paint(v); }

    int cS=comp[1], cT=comp[n];
    if(cS==cT){
        rep(i,q) print(-1);
        return;
    }

    vector<vector<pair<int,int>>> tree(cid+1);
    for(int i=1;i<=m;i++) if(isB[i]){
        auto [u,v]=edges[i];
        int a=comp[u], b=comp[v];
        tree[a].push_back({b,i});
        tree[b].push_back({a,i});
    }

    vector<char> need(m+1,0);
    vector<int> parC(cid+1,-1), parE(cid+1,-1);
    queue<int> qu; qu.push(cS); parC[cS]=cS;
    while(!qu.empty()){
        int v=qu.front(); qu.pop();
        if(v==cT) break;
        for(auto [to,id]: tree[v]){
            if(parC[to]==-1){
                parC[to]=v;
                parE[to]=id;
                qu.push(to);
            }
        }
    }
    int cur=cT;
    while(cur!=cS){
        need[parE[cur]]=1;
        cur=parC[cur];
    }

    vector<int> label(n+1,-1), dist(n+1,INT_MAX), best(n+1,INT_MAX);
    queue<int> qv;
    for(int i=1;i<=m;i++) if(need[i]){
        auto [u,v]=edges[i];
        if(best[u]>i){ best[u]=i; if(dist[u]==INT_MAX){dist[u]=0; label[u]=i; qv.push(u);} else if(label[u]>i) label[u]=i; }
        if(best[v]>i){ best[v]=i; if(dist[v]==INT_MAX){dist[v]=0; label[v]=i; qv.push(v);} else if(label[v]>i) label[v]=i; }
    }
    if(qv.empty()){
        rep(i,q) print(-1);
        return;
    }
    while(!qv.empty()){
        int v=qv.front(); qv.pop();
        for(auto [to,id]: g[v]){
            int nd=dist[v]+1;
            if(nd<dist[to] || (nd==dist[to] && label[v]<label[to])){
                dist[to]=nd;
                label[to]=label[v];
                qv.push(to);
            }
        }
    }
    rep(i,q){
        int v=c[i];
        print(label[v]==-1?-1:label[v]);
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