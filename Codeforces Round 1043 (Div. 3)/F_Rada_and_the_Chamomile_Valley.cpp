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
    int n,m,q; input(n,m,q);
    vector<vector<pair<int,int>>> g(n+1);
    vector<pair<int,int>> edges(m+1);
    for(int i=1;i<=m;i++){
        int u,v; cin>>u>>v;
        edges[i]={u,v};
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }
    vector<int> c(q);
    rep(i,q) cin>>c[i];

    auto bfs=[&](int s){
        const int INF=1e9;
        vector<int> d(n+1,INF);
        deque<int> dq;
        d[s]=0; dq.push_back(s);
        while(!dq.empty()){
            int v=dq.front(); dq.pop_front();
            for(auto [to,id]: g[v]){
                if(d[to]>d[v]+1){
                    d[to]=d[v]+1;
                    dq.push_back(to);
                }
            }
        }
        return d;
    };

    vector<int> ds=bfs(1), dt=bfs(n);
    int L=ds[n];

    vector<int> cnt(L+1,0);
    vector<char> on(n+1,0);
    for(int v=1;v<=n;v++){
        if(ds[v]+dt[v]==L){
            on[v]=1;
            cnt[ds[v]]++;
        }
    }

    vector<char> mand(m+1,0);
    for(int i=1;i<=m;i++){
        auto [u,v]=edges[i];
        if(!on[u]||!on[v]) continue;
        if(abs(ds[u]-ds[v])!=1) continue;
        int a=u,b=v;
        if(ds[a]>ds[b]) swap(a,b);
        if(cnt[ds[a]]==1 && cnt[ds[b]]==1) mand[i]=1;
    }

    vector<int> bestLab(n+1, -1), dist(n+1, INT_MAX);
    if(accumulate(all(mand),0)==0){
        rep(i,q) print(-1);
        return;
    }

    vector<int> minEdgeAt(n+1, INT_MAX);
    for(int i=1;i<=m;i++) if(mand[i]){
        auto [u,v]=edges[i];
        minEdgeAt[u]=std::min(minEdgeAt[u], i);
        minEdgeAt[v]=std::min(minEdgeAt[v], i);
    }

    queue<int> qu;
    for(int v=1;v<=n;v++){
        if(minEdgeAt[v]!=INT_MAX){
            dist[v]=0;
            bestLab[v]=minEdgeAt[v];
            qu.push(v);
        }
    }
    while(!qu.empty()){
        int v=qu.front(); qu.pop();
        for(auto [to,id]: g[v]){
            int nd=dist[v]+1;
            if(nd<dist[to] || (nd==dist[to] && bestLab[v]<bestLab[to])){
                dist[to]=nd;
                bestLab[to]=bestLab[v];
                qu.push(to);
            }
        }
    }

    rep(i,q){
        int v=c[i];
        print(bestLab[v]==-1?-1:bestLab[v]);
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