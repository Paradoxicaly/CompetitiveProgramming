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
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)

const int MOD = 1e9+7;

#ifdef Tomato
template<typename T>
ostream& operator<<(ostream& o, vector<T> v){ o<<"{"; int f=0; for(T x:v) o<<(f++?" ":"")<<x; return o<<"}"; }
void bug__(int c, auto...a){ cerr<<"\e[1;"<<c<<"m"; (..., (cerr<<a<<" ")); cerr<<"\e[0m\n"; }
#define bug_(c,x...) bug__(c,__LINE__,"["+string(#x)+"]",x)
#define bug(x...) bug_(32,x)
#else
#define bug(x...) void(0)
#endif

template<class...T> constexpr auto min(T...a){return std::min({a...});}
template<class...T> constexpr auto max(T...a){return std::max({a...});}
template<class...T> void input(T&...a){(cin>>...>>a);}
template<class T,class...Ts> void print(const T& a, const Ts&...b){ cout<<a; (cout<<...<<(cout<<' ',b)); cout<<"\n"; }
void print(){ cout<<"\n"; }

ll gcd(ll a, ll b){ return b?gcd(b,a%b):a; }

static void factorize(ll N, vector<pair<ll,int>>& fac){
    fac.clear();
    ll t=N;
    for(ll p=2;p*p<=t;p++){
        if(t%p==0){
            int c=0;
            while(t%p==0){ t/=p; c++; }
            fac.emplace_back(p,c);
        }
    }
    if(t>1) fac.emplace_back(t,1);
}

static void gen_divs(int idx, const vector<pair<ll,int>>& fac, ll cur, vector<ll>& divs, vector<vector<int>>& expv, vector<int>& cur_exp){
    if(idx==(int)fac.size()){
        divs.pb(cur);
        expv.pb(cur_exp);
        return;
    }
    ll p=fac[idx].first;
    int emax=fac[idx].second;
    ll val=1;
    for(int e=0;e<=emax;e++){
        cur_exp[idx]=e;
        gen_divs(idx+1,fac,cur*val,divs,expv,cur_exp);
        val*=p;
    }
}

static int compute_f(ll N, ll k){
    if(N==1) return 0;
    vector<pair<ll,int>> fac;
    factorize(N,fac);
    vector<ll> divs;
    vector<vector<int>> expv;
    vector<int> cur_exp(fac.size());
    gen_divs(0,fac,1LL,divs,expv,cur_exp);
    int D=sz(divs);
    vector<int> order(D);
    iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[&](int i,int j){ return divs[i]<divs[j]; });
    vector<ll> divs2(D);
    vector<vector<int>> expv2(D);
    rep(i,D){
        divs2[i]=divs[order[i]];
        expv2[i]=expv[order[i]];
    }
    divs.swap(divs2);
    expv.swap(expv2);
    unordered_map<ll,int> idx;
    idx.reserve(D*2);
    rep(i,D) idx[divs[i]]=i;
    vector<int> dist(D,-1);
    int start=idx[1];
    int target=idx[N];
    deque<int> q;
    dist[start]=0;
    q.pb(start);
    while(!q.empty()){
        int u=q.front(); q.pop_front();
        if(u==target) break;
        ll dv=divs[u];
        ll rem=N/dv;
        rep(vi,D){
            ll f=divs[vi];
            if(f<2||f>k) continue;
            if(rem%f!=0) continue;
            ll nxt=dv*f;
            int ni=idx[nxt];
            if(dist[ni]==-1){
                dist[ni]=dist[u]+1;
                q.pb(ni);
            }
        }
    }
    return dist[target];
}

void solve(){
    ll x,y,k;
    input(x,y,k);
    if(x==y){
        print(0);
        return;
    }
    ll g=gcd(x,y);
    ll X=x/g, Y=y/g;
    int fY=compute_f(Y,k);
    if(fY<0){ print(-1); return; }
    int fX=compute_f(X,k);
    if(fX<0){ print(-1); return; }
    print(fY+fX);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    input(T);
    while(T--) solve();
    return 0;
}
