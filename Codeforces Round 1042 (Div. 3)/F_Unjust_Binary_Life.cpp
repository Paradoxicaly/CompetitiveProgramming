/*
Tomato_Cultivator
*/


#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
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
ostream& operator<<(ostream &o, vector<T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#else
#define bug(x...) void(0)
#endif


template<class... T>
constexpr auto min(T... a){
    return std::min({a...});
}


template<class... T>
constexpr auto max(T... a){
    return std::max({a...});
}


template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}


template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }


ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}


ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}


void solve() {
    int n; input(n);
    string a, b; cin >> a >> b;
    vector<int> pA(n+1,0), pB(n+1,0), prefA(n+1,0), prefB(n+1,0);
    for(int i=1;i<=n;i++){
        pA[i] = (a[i-1]!=a[0]);
        pB[i] = (b[i-1]!=b[0]);
        prefA[i] = prefA[i-1] + pA[i];
        prefB[i] = prefB[i-1] + pB[i];
    }
    int s = (a[0]!=b[0]);
    vector<long long> D(n), U(n), V(n);
    for(int y=1;y<=n;y++){
        long long u, v;
        if(s==0){ u = prefB[y]; v = y - prefB[y]; }
        else { u = y - prefB[y]; v = prefB[y]; }
        U[y-1]=u; V[y-1]=v; D[y-1]=u - v;
    }
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j){ return D[i]<D[j]; });
    vector<long long> keys(n), preU(n+1,0), preV(n+1,0);
    for(int i=0;i<n;i++){
        keys[i]=D[ord[i]];
        preU[i+1]=preU[i]+U[ord[i]];
        preV[i+1]=preV[i]+V[ord[i]];
    }
    long long totV = preV[n];
    long long ans = 0;
    for(int x=1;x<=n;x++){
        long long A = prefA[x];
        long long T = x - 2*A;
        int m = upper_bound(all(keys), T) - keys.begin();
        long long sumU_le = preU[m];
        long long sumV_le = preV[m];
        long long sumV_gt = totV - sumV_le;
        long long Sx = sumU_le + sumV_gt + 1LL*x*(n - m) + A*(2LL*m - n);
        ans += Sx;
    }
    print(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}