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

static inline int ask(int i){
    cout << "? " << (i+1) << '\n';
    cout.flush();
    int x; if(!(cin >> x)) exit(0);
    return x;
}
static inline void say_split(int a, int b){
    cout << "! " << a << ' ' << b << '\n';
    cout.flush();
}
static inline void say_impossible(){
    cout << "! -1\n";
    cout.flush();
}

void solve(){
    int n,k;
    if(!(cin>>n>>k)) return;

    vector<int> head(k), tail(k);
    rep(i,k) head[i] = ask(i);
    rep(i,k) tail[i] = ask(n - k + i);

    int shift = n % k;
    rotate(tail.rbegin(), tail.rbegin() + shift, tail.rend());

    if(n == 2*k){
        say_split(k, k);
        return;
    }
    if(head == tail){
        say_impossible();
        return;
    }

    int ind = 0;
    while(ind < k && head[ind] == tail[ind]) ind++;
    if(ind == k){
        say_impossible();
        return;
    }

    auto f = [&](int b)->bool{
        int idx = b*k + ind;
        if(idx < 0 || idx >= n) return false;
        return ask(idx) == head[ind];
    };

    int maxBlock = (n-1 - ind)/k;

    if(!f(0)){
        say_impossible();
        return;
    }
    if(f(maxBlock)){
        say_impossible();
        return;
    }

    int lo = 0, hi = maxBlock;
    while(hi - lo > 1){
        int mid = (lo + hi) >> 1;
        if(f(mid)) lo = mid;
        else hi = mid;
    }

    int L = lo*k + ind;
    int R = hi*k + ind;

    int last_A = L;
    int first_B = R;

    while(n - first_B < k) first_B--;
    while(last_A + 1 < k) last_A++;

    for(int i = L + 1; i < R; ++i){
        int v = ask(i);
        int m = i % k;
        bool inA = (v == head[m]);
        bool inB = (v == tail[m]);
        if(inA && !inB) last_A = max(last_A, i);
        if(inB && !inA) first_B = min(first_B, i);
    }

    if(first_B - last_A - 1 > 0){
        say_impossible();
        return;
    }

    int aLen = first_B;
    int bLen = n - aLen;
    if(aLen < k || bLen < k){
        say_impossible();
        return;
    }
    say_split(aLen, bLen);
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