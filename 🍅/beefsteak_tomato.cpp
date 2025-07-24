/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

const int INF = 1e9 + 7;
const ll LINF = 1e18;
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

ll lcm(ll a, ll b) { 
    return a / gcd(a, b) * b; 
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

ll modinv(ll a, ll mod = MOD) {
    return power(a, mod - 2, mod);
}

vector<ll> fact, inv_fact;
void precompute_factorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    rng(i, 1, n + 1) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = modinv(fact[n]);
    for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

template<class T>
struct FenwickTree {
    vector<T> tree;
    int n;
    
    FenwickTree(int n) : n(n) {
        tree.assign(n + 1, T{});
    }
    
    void update(int i, T delta) {
        for (++i; i <= n; i += i & -i)
            tree[i] += delta;
    }
    
    T query(int i) {
        T sum{};
        for (++i; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
    
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

struct DSU {
    vi parent, rank;
    
    DSU(int n) : parent(n), rank(n, 0) {
        rep(i, n) parent[i] = i;
    }
    
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

vi adj[200005];
vi visited, parent, depth;

void dfs(int v, int par = -1) {
    visited[v] = 1;
    parent[v] = par;
    for (int u : adj[v]) {
        if (u != par && !visited[u]) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

vi bfs(int start, int n) {
    queue<int> q;
    vi dist(n, -1);
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist;
}

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    ll operator*(const Point& p) const { return x * p.x + y * p.y; }
    ll operator^(const Point& p) const { return x * p.y - y * p.x; }
    ll norm2() const { return x * x + y * y; }
};

ll orientation(Point a, Point b, Point c) {
    return (b - a) ^ (c - a);
}

void solve() {
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}