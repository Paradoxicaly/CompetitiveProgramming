/*
Tomato_Cultivator
beefsteak tomato
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

template<class T>
istream& operator>>(istream &in, vector<T> &a) {
    for (auto &x : a) in >> x;
    return in;
}

struct Node {
    int sum, pref, suff, best;
    Node() : sum(0), pref(0), suff(0), best(0) {}
    Node(int x) : sum(x), pref(max(0, x)), suff(max(0, x)), best(max(0, x)) {}
};

Node merge(const Node &L, const Node &R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.best = max({L.best, R.best, L.suff + R.pref});
    return res;
}

struct segtree {
    int n;
    vector<Node> st;
    segtree(int _n) : n(_n), st(4 * n) {
        build(1, 0, n - 1);
    }
    void build(int p, int l, int r) {
        if (l == r) {
            st[p] = Node(-1);
            return;
        }
        int m = (l + r) / 2;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = Node(val);
            return;
        }
        int m = (l + r) / 2;
        if (idx <= m) update(p << 1, l, m, idx, val);
        else update(p << 1 | 1, m + 1, r, idx, val);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
    Node query(int p, int l, int r, int i, int j) {
        if (i > r || j < l) return Node(INT_MIN);
        if (l >= i && r <= j) return st[p];
        int m = (l + r) / 2;
        Node L = query(p << 1, l, m, i, j);
        Node R = query(p << 1 | 1, m + 1, r, i, j);
        if (L.best == INT_MIN) return R;
        if (R.best == INT_MIN) return L;
        return merge(L, R);
    }
    int max_subarray() {
        return query(1, 0, n - 1, 0, n - 1).best;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    cin >> a;
    vector<vi> at(n + 1);
    rep(i, n) at[a[i]].pb(i);
    vector<vector<array<int, 3>>> updates(n + 1);
    rep(idx, q) {
        int i, x;
        cin >> i >> x;
        --i;
        if (x != a[i]) {
            updates[a[i]].pb({idx, i, -1});
            a[i] = x;
            updates[x].pb({idx, i, 1});
        }
    }
    vector<vi> final_at(n + 1);
    rep(i, n) final_at[a[i]].pb(i);
    segtree st(n);
    vi init(n + 1);
    vector<vector<pii>> change(q);
    rng(x, 1, n + 1) {
        for (int i : at[x]) st.update(i, 1);
        int cur = st.max_subarray();
        init[x] = cur;
        for (auto &i : updates[x]) {
            st.update(i[1], i[2]);
            int new_cur = st.max_subarray();
            change[i[0]].pb({cur, new_cur});
            cur = new_cur;
        }
        for (int i : final_at[x]) st.update(i, -1);
    }
    multiset<int> ms;
    rng(i, 1, n + 1) ms.insert(init[i]);
    rep(i, q) {
        for (auto &j : change[i]) {
            ms.erase(ms.find(j.fi));
            ms.insert(j.se);
        }
        cout << *prev(ms.end()) / 2 << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) solve();
}