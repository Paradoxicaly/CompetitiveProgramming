/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())

const int MOD = 1000000007;
const int MAXV = 1000005;

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, const vector<T>& v) {
    o << "{"; int f = 0;
    for (auto &x : v) o << (f++ ? " " : "") << x;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m\n";
}
#define bug(x...) bug__(32, x)
#else
#define bug(...) void(0)
#endif

ll modpow(ll a, ll b, ll m = MOD) {
    a %= m; ll r = 1;
    while (b) {
        if (b & 1) r = r * a % m, --b;
        a = a * a % m; b >>= 1;
    }
    return r;
}

vector<int> graphAdj[MAXV];
int depthArr[MAXV];
int sizeArr[MAXV];
vector<int> leafs;
int cent;

void dfsTree(int u, int p) {
    bool isLeaf = true;
    int childCount = sz(graphAdj[u]) - (u != 1);
    if (childCount == 2) cent = u;
    sizeArr[u] = 1;
    for (int v : graphAdj[u]) {
        if (v == p) continue;
        isLeaf = false;
        depthArr[v] = depthArr[u] + 1;
        dfsTree(v, u);
        sizeArr[u] += sizeArr[v];
    }
    if (isLeaf) leafs.pb(u);
}

void solve() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        graphAdj[i].clear();
        depthArr[i] = 0;
    }
    leafs.clear();
    cent = 0;
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        cin >> x >> y;
        graphAdj[x].pb(y);
        graphAdj[y].pb(x);
    }
    dfsTree(1, 0);
    if (sz(leafs) > 2) {
        cout << 0 << "\n";
        return;
    }
    if (sz(leafs) == 1) {
        cout << modpow(2, N) << "\n";
        return;
    }
    ll res = 0;
    int aNode = leafs[0], bNode = leafs[1];
    if (depthArr[aNode] == depthArr[bNode]) {
        int temp = N - sizeArr[cent] + 2;
        cout << modpow(2, temp) << "\n";
        return;
    }
    if (depthArr[aNode] < depthArr[bNode]) swap(aNode, bNode);
    int diff = depthArr[bNode] - depthArr[cent];
    int caseOne = N - 2*diff - 1;
    int caseTwo = N - 2*diff;
    res = (modpow(2, caseOne) + modpow(2, caseTwo)) % MOD;
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}