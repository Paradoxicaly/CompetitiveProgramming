/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

#ifdef Doludu
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


void solve() {
    int n;
    input(n);

    vector<vector<int>> adj(n);
    rep(i, n - 1) {
        int u, v;
        input(u, v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int rt = -1;
    rep(i, n) {
        if (sz(adj[i]) == 2) {
            rt = i;
            break;
        }
    }

    if (rt == -1) {
        print("NO");
        return;
    }

    vector<pair<int, int>> res;

    function<void(int, int, int)> dfs = [&](int u, int fa, int val) -> void {
        if (val) {
            res.pb({u, fa});
        } else {
            res.pb({fa, u});
        }
        for (int v : adj[u]) {
            if (v != fa) {
                dfs(v, u, val ^ 1);
            }
        }
    };

    dfs(adj[rt][0], rt, 0);
    dfs(adj[rt][1], rt, 1);

    print("YES");
    for (auto& [x, y] : res) {
        print(x + 1, y + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while (T--) solve();
    return 0;
}