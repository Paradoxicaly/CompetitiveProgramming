/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using str = string;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

template<class T> using V = vector<T>;
template<class T, size_t SZ> using AR = array<T, SZ>;

const int MOD = 1e9 + 7;
const db PI = acos((db)-1);

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, true : false; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, true : false; }

template<typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E), T(*ti)(), E (*ei)()>
struct LazySegTree {
    int n, log, size;
    V<T> val; V<E> laz;
    LazySegTree() {}
    LazySegTree(const V<T>& v) { init(v); }

    void init(const V<T>& v) {
        size = v.size();
        n = 1, log = 0;
        while (n < size) n <<= 1, ++log;
        val.assign(2 * n, ti());
        laz.assign(n, ei());
        rep(i, size) val[i + n] = v[i];
        for (int i = n - 1; i > 0; --i) pull(i);
    }

    void update(int l, int r, E const& x) {
        if (l >= r) return;
        l += n, r += n;
        for (int i = log; i >= 1; --i) {
            if ((l >> i) << i != l) push(l >> i);
            if ((r >> i) << i != r) push((r - 1) >> i);
        }
        int l0 = l, r0 = r;
        while (l < r) {
            if (l & 1) apply(l++, x);
            if (r & 1) apply(--r, x);
            l >>= 1; r >>= 1;
        }
        l = l0; r = r0;
        for (int i = 1; i <= log; ++i) {
            if ((l >> i) << i != l) pull(l >> i);
            if ((r >> i) << i != r) pull((r - 1) >> i);
        }
    }

    T query(int l, int r) {
        if (l >= r) return ti();
        l += n, r += n;
        for (int i = log; i >= 1; --i) {
            if ((l >> i) << i != l) push(l >> i);
            if ((r >> i) << i != r) push((r - 1) >> i);
        }
        T resL = ti(), resR = ti();
        while (l < r) {
            if (l & 1) resL = f(resL, val[l++]);
            if (r & 1) resR = f(val[--r], resR);
            l >>= 1; r >>= 1;
        }
        return f(resL, resR);
    }

    void set_val(int i, T const& x) {
        i += n;
        for (int j = log; j >= 1; --j) push(i >> j);
        val[i] = x;
        for (int j = 1; j <= log; ++j) pull(i >> j);
    }

private:
    void pull(int i) { val[i] = f(val[2 * i], val[2 * i + 1]); }
    void apply(int i, E const& x) {
        val[i] = g(val[i], x);
        if (i < n) laz[i] = laz[i] == ei() ? x : h(laz[i], x);
    }
    void push(int i) {
        if (laz[i] != ei()) {
            apply(2 * i, laz[i]);
            apply(2 * i + 1, laz[i]);
            laz[i] = ei();
        }
    }
};

using T = db;
using E = db;
T f(T a, T b) { return max(a, b); }
T g(T a, E b) { return a + b; }
E h(E a, E b) { return a + b; }
T ti() { return -1e12; }
E ei() { return 0; }

using SegTree = LazySegTree<T, E, f, g, h, ti, ei>;

db solve(int N, int K, V<int> A, V<int> B, V<int> C, V<int> D) {
    V<db> a(N), b(N), c(N), d(N);
    rep(i, N) {
        a[i] = A[i];
        b[i] = B[i];
        c[i] = C[i];
        d[i] = D[i];
    }

    db l = 0, r = 2e6;
    while (r - l > 1e-6) {
        db x = (l + r) / 2.0;
        V<db> v(N + 1);
        SegTree st(v);
        V<db> dp(N + 1);
        for (int i = N - 1; i >= 0; --i) {
            db option1 = dp[i + 1];
            db option2 = st.query(min(N, i + K + 1), N + 1);
            dp[i] = a[i] - x * b[i] + max(option1, option2);
            st.update(i, i + 1, dp[i]);
            st.update(i + 1, N + 1, a[i] + c[i] - x * d[i]);
        }
        if (dp[0] >= 0) l = x;
        else r = x;
    }
    return l;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(7);
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        V<int> A(N), B(N), C(N), D(N);
        rep(i, N) cin >> A[i];
        rep(i, N) cin >> B[i];
        rep(i, N) cin >> C[i];
        rep(i, N) cin >> D[i];
        cout << solve(N, K, A, B, C, D) << '\n';
    }
    return 0;
}