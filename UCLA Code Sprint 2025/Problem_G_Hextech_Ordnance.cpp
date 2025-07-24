/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
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
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif

struct node {
    int mn, mx;
};

struct pqn {
    int val, i, j;
};

struct cmp {
    bool operator()(const pqn &a, const pqn &b) const {
        return a.val > b.val;
    }
};

int n;
vector<int> a;
vector<node> st;

void build(int p, int l, int r) {
    if (l == r) {
        st[p].mn = st[p].mx = a[l];
    } else {
        int m = (l + r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        st[p].mn = min(st[p << 1].mn, st[p << 1 | 1].mn);
        st[p].mx = max(st[p << 1].mx, st[p << 1 | 1].mx);
    }
}

node query(int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) return st[p];
    int m = (l + r) >> 1;
    if (j <= m) return query(p << 1, l, m, i, j);
    if (i > m) return query(p << 1 | 1, m + 1, r, i, j);
    node L = query(p << 1, l, m, i, j);
    node R = query(p << 1 | 1, m + 1, r, i, j);
    return {min(L.mn, R.mn), max(L.mx, R.mx)};
}

void solve() {
    cin >> n;
    a.resize(n);
    rep(i, n) cin >> a[i];

    if (n <= 2) {
        cout << "unstable\n";
        return;
    }

    st.resize(4 * n);
    build(1, 0, n - 1);

    priority_queue<pqn, vector<pqn>, cmp> pq;
    rep(i, n - 1) {
        int d = abs(a[i + 1] - a[i]);
        pq.push({d, i, i + 1});
    }

    rng(k, 1, n + 1) {
        if (pq.empty()) {
            cout << "unstable\n";
            return;
        }
        auto cur = pq.top(); pq.pop();
        if (cur.val > k) {
            cout << "unstable\n";
            return;
        }
        if (cur.j + 1 < n) {
            int nj = cur.j + 1;
            node q = query(1, 0, n - 1, cur.i, nj);
            int nd = q.mx - q.mn;
            pq.push({nd, cur.i, nj});
        }
    }

    cout << "stable\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}