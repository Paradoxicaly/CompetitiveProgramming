/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)

#ifdef Tomato
template<typename T>
ostream& operator<<(ostream &o, vector<T> v){
    o<<"{"; int f=0;
    for(auto &x:v) o<<(f++?" ":"")<<x;
    return o<<"}";
}
void bug__(int c, auto...a){
    cerr<<"\e[1;"<<c<<"m";
    (...,(cerr<<a<<" "));
    cerr<<"\e[0m"<<endl;
}
#define bug(x...) bug__(32, x)
#else
#define bug(x...) void(0)
#endif

template<class... T>
void input(T&... a){ (cin>>...>>a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout<<a; (cout<<...<<(cout<<' ',b)); cout<<'\n';
}
void print(){ cout<<'\n'; }

void solve(){
    int n, m;
    input(n, m);
    vector<vector<int>> a(n, vector<int>(m, -1));
    auto Print = [&](int i, int j){
        cout<<i+1<<" "<<j+1<<"\n";
        int bestD1 = -1, bestD2 = -1;
        vector<pair<int,int>> cells;
        rep(r, n) rep(c, m){
            if(a[r][c] < 0) continue;
            int d1 = max(abs(r - i), abs(c - j));
            int d2 = abs(r - i) + abs(c - j);
            if(d1 > bestD1 || (d1 == bestD1 && d2 > bestD2)){
                bestD1 = d1; bestD2 = d2;
                cells.clear();
            }
            if(d1 == bestD1 && d2 == bestD2){
                cells.emplace_back(r, c);
            }
        }
        for(auto &p : cells){
            a[p.fi][p.se] += 1;
        }
        a[i][j] = 0;
    };

    int i1 = n/2, i2 = n/2;
    int j1 = m/2, j2 = m/2;
    Print(i1, j1);
    while(i1 > 0 || j1 > 0){
        if(i1 > 0){
            --i1; ++i2;
            for(int j = m/2; j >= j1; --j){
                Print(i1, j);
                Print(i2, j);
                if(j < m/2){
                    Print(i1, m-1-j);
                    Print(i2, m-1-j);
                }
            }
        }
        if(j1 > 0){
            --j1; ++j2;
            for(int i = n/2; i >= i1; --i){
                Print(i, j1);
                Print(i, j2);
                if(i < n/2){
                    Print(n-1-i, j1);
                    Print(n-1-i, j2);
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while(T--) solve();
    return 0;
}