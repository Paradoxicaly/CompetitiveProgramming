/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9+7;

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, vector<T> v) {
    o << "{"; int f=0; for (auto &x:v) o << (f++?" ":"") << x;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;"<<c<<"m"; (..., (cerr<<a<<" ")); cerr<<"\e[0m\n";
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
void input(T&... a) { (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}

int mul(ll a, ll b) { return int((a*b) % MOD); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    static vector<int> fact(200001);
    fact[0]=1;
    for(int i=1;i<=200000;i++) fact[i]=mul(fact[i-1], i);

    int T; input(T);
    while(T--){
        int n,m; input(n,m);
        vector<vector<int>> adj(n+1);
        for(int i=0;i<m;i++){int u,v; input(u,v); adj[u].push_back(v); adj[v].push_back(u);}
        vector<int> color(n+1,-1);
        bool ok=true;
        ll ans=1;
        for(int s=1;s<=n;s++){
            if(color[s]!=-1) continue;
            queue<int> q;
            color[s]=0; q.push(s);
            vector<int> comp;
            vector<int> side[2];
            while(!q.empty() && ok){
                int u=q.front(); q.pop();
                comp.push_back(u);
                side[color[u]].push_back(u);
                for(int v:adj[u]){
                    if(color[v]==-1){ color[v]=color[u]^1; q.push(v); }
                    else if(color[v]==color[u]){ ok=false; break; }
                }
            }
            if(!ok) break;

            for(int c0=0;c0<2;c0++){
                vector<vector<int>> neighs;
                for(int u: side[c0]){
                    auto L=adj[u];
                    sort(L.begin(),L.end());
                    neighs.push_back(L);
                }
                sort(neighs.begin(), neighs.end());
                for(int i=1;i<(int)neighs.size();i++){
                    auto &A = neighs[i-1], &B = neighs[i];
                    auto it = B.begin();
                    for(int x:A){
                        it = lower_bound(it, B.end(), x);
                        if(it==B.end()||*it!=x){ ok=false; break; }
                    }
                    if(!ok) break;
                }
                if(!ok) break;
                for(int i=0,j;i<(int)neighs.size();i=j){
                    j=i+1;
                    while(j<(int)neighs.size() && neighs[j]==neighs[i]) j++;
                    ans = mul(ans, fact[j-i]);
                }
            }
            if(!ok) break;
            ans = mul(ans, 2);
        }
        print(ok ? int(ans) : 0);
    }
    return 0;
}
