/*
Tomato_Cultivator 
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
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
void print() { cout << '\n'; }

struct Edge{ int u,v; };

struct Solver {
    int n,m;
    vector<Edge> E;
    vector<char> active;
    vector<int> rem;
    int best;

    struct Op{ int type,e,u,v,ru,rv; };

    void include_edge(int e, vector<Op>& st, int& cur){
        int u=E[e].u, v=E[e].v;
        st.push_back({1,e,u,v,rem[u],rem[v]});
        active[e]=0; --rem[u]; --rem[v]; ++cur;
    }
    void exclude_edge(int e, vector<Op>& st){
        st.push_back({2,e,0,0,0,0});
        active[e]=0;
    }
    void undo(vector<Op>& st, int k, int& cur){
        while((int)st.size()>k){
            auto op=st.back(); st.pop_back();
            if(op.type==1){ active[op.e]=1; rem[op.u]=op.ru; rem[op.v]=op.rv; --cur; }
            else{ active[op.e]=1; }
        }
    }

    void propagate(vector<Op>& st, int& cur){
        while(true){
            bool changed=false;
            vector<int> feasCnt(n+1,0);
            vector<vi> feasEdges(n+1);
            rep(e,m){
                if(!active[e]) continue;
                int u=E[e].u, v=E[e].v;
                if(rem[u]>0 && rem[v]>0){
                    ++feasCnt[u]; feasEdges[u].pb(e);
                    ++feasCnt[v]; feasEdges[v].pb(e);
                }
            }
            for(int v=1; v<=n; ++v){
                if(rem[v]==0) continue;
                if(feasCnt[v]==rem[v] && feasCnt[v]>0){
                    for(int e:feasEdges[v]){
                        if(!active[e]) continue;
                        int u=E[e].u, w=E[e].v;
                        if(rem[u]==0 || rem[w]==0) continue;
                        include_edge(e, st, cur);
                        changed=true;
                    }
                }
            }
            if(!changed) return;
        }
    }

    int upper_bound_est(){
        vector<int> feas(n+1,0);
        rep(e,m){
            if(!active[e]) continue;
            int u=E[e].u, v=E[e].v;
            if(rem[u]>0 && rem[v]>0){ ++feas[u]; ++feas[v]; }
        }
        long long s=0;
        for(int v=1; v<=n; ++v) s += min(rem[v],feas[v]);
        return (int)(s/2);
    }

    int pick_edge(){
        vector<int> feas(n+1,0);
        rep(e,m){
            if(!active[e]) continue;
            int u=E[e].u, v=E[e].v;
            if(rem[u]>0 && rem[v]>0){ ++feas[u]; ++feas[v]; }
        }
        int be=-1, bs=-1;
        rep(e,m){
            if(!active[e]) continue;
            int u=E[e].u, v=E[e].v;
            if(rem[u]==0 || rem[v]==0) continue;
            int sc=feas[u]+feas[v];
            if(sc>bs){ bs=sc; be=e; }
        }
        return be;
    }

    void dfs(int cur){
        vector<Op> st;
        int snap=sz(st);
        propagate(st,cur);

        int ub = cur + upper_bound_est();
        if(ub<=best){ undo(st,snap,cur); return; }

        int e = pick_edge();
        if(e==-1){ best=max(best,cur); undo(st,snap,cur); return; }

        {
            int mark=sz(st);
            include_edge(e,st,cur);
            dfs(cur);
            undo(st,mark,cur);
        }
        {
            int mark=sz(st);
            exclude_edge(e,st);
            dfs(cur);
            undo(st,mark,cur);
        }
        undo(st,snap,cur);
    }

    int run(int _n, int _m, const vector<pii>& ed){
        n=_n; m=_m;
        E.resize(m);
        rep(i,m) E[i]={ed[i].fi, ed[i].se};
        active.assign(m,1);
        rem.assign(n+1,2);
        best=0; int cur=0;
        dfs(cur);
        return best;
    }
};

void solve(){
    int t; input(t);
    while(t--){
        int n,m; input(n,m);
        vector<pii> ed(m);
        rep(i,m){ int u,v; input(u,v); ed[i]={u,v}; }
        Solver S;
        print(S.run(n,m,ed));
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}