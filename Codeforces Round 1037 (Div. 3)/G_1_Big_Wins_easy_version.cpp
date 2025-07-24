/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())
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

const int mod = 998244353, N = 1000005;

struct DS {
    ll pre, suf, sum, ans;
    DS(int x = 0) : pre(max(x, 0)), suf(max(x, 0)), sum(x), ans(max(x, 0)) {}
    DS operator+(const DS &o) const {
        DS res(0);
        res.pre = max(pre, sum + o.pre);
        res.suf = max(o.suf, suf + o.sum);
        res.sum = sum + o.sum;
        res.ans = max({ans, o.ans, suf + o.pre});
        return res;
    }
};

DS tree[N << 1];
int _n;

void modify(int p, int x) {
    for (tree[p += _n] = DS(x), p >>= 1; p; p >>= 1)
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

DS query(int l, int r) {
    DS resl(0), resr(0);
    for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) resl = resl + tree[l++];
        if (r & 1) resr = tree[--r] + resr;
    }
    return resl + resr;
}

void reset() {
    rep(i, _n * 2) tree[i] = DS(0);
}

void solve() {
    int n;
    cin >> n;
    _n = n;
    vector<int> a(n);
    vector<vector<int>> block(n);
    rep(i, n) {
        cin >> a[i], --a[i];
        block[a[i]].pb(i);
    }
    rep(i, n) modify(i, 1);
    int ans = 0;
    auto check = [&](int pos) {
        DS pre = (!pos ? DS(0) : query(0, pos));
        DS suf = (pos + 1 < n ? query(pos + 1, n) : DS(0));
        return pre.suf - 1 + suf.pre >= 0;
    };
    for (int i = 0, j = 0; i < n; ++i) {
        for (int pos : block[i]) {
            while (j <= i || check(pos)) {
                for (int p : block[j])
                    modify(p, -1);
                j++;
            }
        }
        bug(i, j);
        ans = max(ans, j - i - 1);
        for (int pos : block[i])
            modify(pos, -1 << 30);
    }
    cout << ans << '\n';
    reset();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
}