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

namespace {
    const int MAXN = 100000 + 7;
    int A[MAXN], L_[11343 + 5], R_[11343 + 5];
    const int B = 116;

    inline void query(int n, int a[]){
        cout << "? " << n << ' ';
        for(int i = 1; i <= n; ++i){
            cout << a[i] << (i==n?'\n':' ');
        }
        cout.flush();
    }

    void init_blocks(){
        static bool inited = false;
        if(inited) return;
        for(int i = 1; i <= 862; ++i){
            int res = 11343 / i + (11343 % i != 0);
            if(L_[res] == 0) L_[res] = i;
            R_[res] = i;
        }
        for(int i = 1; i <= 11343; ++i){
            L_[i] = L_[i] * B;
            R_[i] = min(R_[i] * B + B - 1, 100000);
        }
        L_[0] = 1; R_[0] = B - 1;
        inited = true;
    }
}

void solve(){
    init_blocks();

    int n = 11343;
    for(int i = 1; i <= n; ++i) A[i] = B;
    query(n, A);

    int len = 0; 
    cin >> len;

    int nowl = L_[len], nowr = R_[len];

    if(2 * nowl > nowr){
        n = nowr - nowl;
        for(int i = 1, cnt = 1; i <= n + n; i += 2, ++cnt){
            A[i] = nowl;
            A[i+1] = cnt;
        }
        query(n << 1, A);
        cin >> len;
        int x = 2 * n - len;
        cout << "! " << nowl + x << '\n';
    }else{
        n = B * B;
        for(int i = 1; i <= n; ++i) A[i] = 1;
        query(n, A);
        cin >> len;
        assert(len != 0);
        cout << "! " << (n / len + (n % len != 0)) << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    if(cin >> T){
        while(T--) solve();
    }
    return 0;
}
