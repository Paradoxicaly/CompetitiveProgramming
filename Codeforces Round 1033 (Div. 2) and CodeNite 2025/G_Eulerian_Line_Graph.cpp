/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
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

vector<vll> v;

bool EulerCycle(ll k) {
    ll odd = 0, n = sz(v);
    rep(i, n) if (sz(v[i]) % 2) odd++;
    if (odd == 0) return true;
    rep(i, n) rep(j, sz(v[i])) {
        if (sz(v[v[i][j]]) % 2 == sz(v[i]) % 2) return false;
    }
    if (k >= 2) return true;
    return false;
}

ll LongestTrailingPath(ll n, ll p) {
    if (sz(v[n]) > 2) return 0;
    rep(i, sz(v[n])) if (v[n][i] != p) return 1 + LongestTrailingPath(v[n][i], n);
    return 0;
}

void MarkVisited(ll n, vll &vis, vector<vll> &adj) {
    vis[n] = 1;
    rep(i, sz(adj[n])) {
        if (!vis[adj[n][i]]) MarkVisited(adj[n][i], vis, adj);
    }
}

bool EulerPath(ll k) {
    ll oddv[2], temp = 0, n = sz(v);
    rep(i, n) if (sz(v[i]) % 2) oddv[temp++] = i;
    ll l[2] = {LongestTrailingPath(oddv[0], -1), LongestTrailingPath(oddv[1], -1)};
    if (l[0] > l[1]) swap(l[0], l[1]), swap(oddv[0], oddv[1]);
    if (l[0] >= k) return true;
    if (l[0] > 0) return false;
    if (l[1] == 1 && sz(v[oddv[0]]) == 3 && v[oddv[1]][0] == oddv[0]) return true;
    if (find(all(v[oddv[0]]), oddv[1]) != end(v[oddv[0]])) return false;
    if (k == 1 || k >= 3) return false;

    auto tempv = v;
    vll vis(n), noniso;

    rep(i, n) {
        auto &vv = tempv[i];
        vv.erase(remove(all(vv), oddv[0]), vv.end());
        vv.erase(remove(all(vv), oddv[1]), vv.end());
        if (sz(vv) > 0 && i != oddv[0] && i != oddv[1]) noniso.pb(i);
    }

    MarkVisited(noniso[0], vis, tempv);
    for (ll u : noniso) if (!vis[u]) return false;

    ll cntedge = 0;
    for (ll u : noniso) {
        int temp = 0;
        if (find(all(v[u]), oddv[0]) != end(v[u])) cntedge++, temp++;
        if (find(all(v[u]), oddv[1]) != end(v[u])) cntedge++, temp++;
        if (temp && sz(v[u]) > 2) return false;
    }
    if (cntedge > 2) return false;

    return true;
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    v.assign(n, {});
    rep(i, m) {
        ll x, y;
        cin >> x >> y;
        --x, --y;
        v[x].pb(y);
        v[y].pb(x);
    }
    if (EulerCycle(k) || EulerPath(k)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}