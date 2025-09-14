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

void solve(){
    int n,m; long long x,y; cin>>n>>m>>x>>y;
    vi a(n), b(m);
    rep(i,n) cin>>a[i];
    rep(i,m) cin>>b[i];
    cout<< (long long)n + m <<'\n';
}
int main(){
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   int T; if(!(cin>>T)) return 0;
   while(T--) solve();
   return 0;
}