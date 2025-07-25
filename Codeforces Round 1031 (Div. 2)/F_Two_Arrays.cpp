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

struct DSU {
    int n;
    vi parent, parity;
    DSU(int _n) : n(_n), parent(n+1), parity(n+1, 0) {
        rng(i,1,n+1) parent[i] = i;
    }
    pii find(int x) {
        if (parent[x] == x) return {x, 0};
        auto pr = find(parent[x]);
        parent[x] = pr.fi;
        parity[x] ^= pr.se;
        return {parent[x], parity[x]};
    }
    void unite(int x, int y, int w) {
        auto [rx, px] = find(x);
        auto [ry, py] = find(y);
        if (rx == ry) return;
        parent[rx] = ry;
        parity[rx] = px ^ py ^ w;
    }
};

void solve() {
    int n;
    input(n);
    vi a(n+1), b(n+1);
    rng(i, 1, n+1) input(a[i]);
    rng(i, 1, n+1) input(b[i]);

    int maxVal = 2 * n;
    vi loops(maxVal+1);
    vector<vector<pii>> occ(maxVal+1);

    rng(i,1,n+1){
        if (a[i] == b[i]) loops[a[i]]++;
        else {
            occ[a[i]].emplace_back(i, 0);
            occ[b[i]].emplace_back(i, 1);
        }
    }

    DSU dsu(n);
    rng(x,1,maxVal+1){
        if (loops[x]) continue;
        if (sz(occ[x]) >= 2) {
            auto [i, pi] = occ[x][0];
            auto [j, pj] = occ[x][1];
            int w = pi ^ pj ^ 1;
            dsu.unite(i, j, w);
        }
    }

    vi s(n+1);
    rng(i,1,n+1){
        s[i] = dsu.find(i).se;
        if (a[i] == b[i]) s[i] = 0;
    }

    vi A(n+1), B(n+1);
    vector<bool> seenA(maxVal+1), seenB(maxVal+1);
    int cntA = 0, cntB = 0;

    rng(i,1,n+1){
        if (s[i] == 0){
            A[i] = a[i];
            B[i] = b[i];
        } else {
            A[i] = b[i];
            B[i] = a[i];
        }
        if (!seenA[A[i]]) seenA[A[i]] = 1, cntA++;
        if (!seenB[B[i]]) seenB[B[i]] = 1, cntB++;
    }

    print(cntA + cntB);
    rng(i,1,n+1) cout << A[i] << " ";
    cout << '\n';
    rng(i,1,n+1) cout << B[i] << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while (T--) solve();
    return 0;
}
