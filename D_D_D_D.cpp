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
    int n, m, L;
    input(n, m, L);
    vi A(L);
    rep(i, L) input(A[i]);
    vector<vi> adj(n+1);
    rep(i, m) {
        int u, v;
        input(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vi dist(n+1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    bool is_bip = true;
    rng(u, 1, n+1) {
        for (int v : adj[u]) {
            if ((dist[u] & 1) == (dist[v] & 1)) {
                is_bip = false;
                break;
            }
        }
        if (!is_bip) break;
    }

    ll S = 0;
    int smallest_odd = INT_MAX;
    for (int k : A) {
        S += k;
        if (k & 1) smallest_odd = min(smallest_odd, k);
    }

    ll s_max_even = -1, s_max_odd = -1;
    if ((S & 1) == 0) {
        s_max_even = S;
        if (smallest_odd < INT_MAX) s_max_odd = S - smallest_odd;
    } else {
        s_max_odd = S;
        if (smallest_odd < INT_MAX) s_max_even = S - smallest_odd;
    }

    string ans;
    ans.reserve(n);
    rng(i, 1, n+1) {
        int d = dist[i];
        if (d < 0) {
            ans.pb('0');
        } else if (!is_bip) {
            ans.pb((S >= d ? '1' : '0'));
        } else {
            ll smax = (d & 1) ? s_max_odd : s_max_even;
            ans.pb((smax >= d ? '1' : '0'));
        }
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
