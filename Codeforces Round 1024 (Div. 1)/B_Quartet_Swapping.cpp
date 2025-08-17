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

template<class T> bool chmin(T& a, const T& b){ if (b < a){ a = b; return true; } return false; }
template<class T> bool chmax(T& a, const T& b){ if (a < b){ a = b; return true; } return false; }

struct Fenwick {
    vector<int> bit;
    int n;
    Fenwick(int n): n(n), bit(n+1,0){}
    void add(int i,int v){
        for(++i;i<=n;i+=i&-i) bit[i]+=v;
    }
    int sum(int i){
        int r=0;
        for(++i;i>0;i-=i&-i) r+=bit[i];
        return r;
    }
};

int invpar(const vi& v,int n){
    Fenwick ft(n);
    long long inv=0;
    for(int i=sz(v)-1;i>=0;--i){
        inv += ft.sum(v[i]-1);
        ft.add(v[i],1);
    }
    return (int)(inv&1);
}

void solve(){
    int n; cin>>n;
    vi a(n), odd, even;
    rep(i,n){
        cin>>a[i];
        --a[i];
        if(i%2==0) odd.pb(a[i]);
        else even.pb(a[i]);
    }
    long long bad = invpar(odd,n) + invpar(even,n);

    sort(all(odd));
    sort(all(even));

    vi res(n);
    int oi=0, ei=0;
    rep(i,n){
        if(i%2==0) res[i]=odd[oi++];
        else res[i]=even[ei++];
    }

    if((bad & 1) && n>=3) swap(res[n-1],res[n-3]);

    rep(i,n) cout<<res[i]+1<<(i==n-1?'\n':' ');
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if(!(cin >> T)) return 0;
    while(T--) solve();

    return 0;
}