/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using ll = long long;
using db = long double;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

template<class T> using V = vector<T>;
template<class T, size_t SZ> using AR = array<T, SZ>;

const int MOD = 1e9 + 7;

template<int MOD, int RT> struct mint {
    static const int mod = MOD;
    int v;
    explicit operator int() const { return v; }
    mint():v(0) {}
    mint(ll _v) { v = int((_v % MOD + MOD) % MOD); }

    mint& operator+=(mint o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int((ll)v * o.v % MOD); return *this; }
    mint& operator/=(mint o) { return *this *= inv(o); }

    friend mint pow(mint a, ll p) {
        mint res = 1;
        while (p) { if (p & 1) res *= a; a *= a; p >>= 1; }
        return res;
    }
    friend mint inv(mint a) { return pow(a, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
};
using mi = mint<MOD, 5>;
using vmi = V<mi>;
using pmi = pair<mi, mi>;

using Mat = V<vmi>;
Mat make_id(int n) {
    Mat m(n, vmi(n));
    rep(i, n) m[i][i] = 1;
    return m;
}
Mat operator*(const Mat &a, const Mat &b) {
    int n = a.size(), m = b[0].size(), p = b.size();
    Mat c(n, vmi(m));
    rep(i, n) rep(j, p) rep(k, m) c[i][k] += a[i][j] * b[j][k];
    return c;
}
vmi operator*(const Mat &a, const vmi &b) {
    int n = a.size(), m = b.size();
    vmi c(n);
    rep(i, n) rep(j, m) c[i] += a[i][j] * b[j];
    return c;
}
pair<Mat, vmi> operator*(const pair<Mat, vmi> &P, const pair<Mat, vmi> &Q) {
    Mat A = P.fi, C = Q.fi;
    vmi B = P.se, D = Q.se;
    Mat E = A * C;
    vmi F = A * D;
    rep(i, F.size()) F[i] += B[i];
    return {E, F};
}
pair<Mat, vmi> mpow(pair<Mat, vmi> A, ll p) {
    int n = A.fi.size();
    pair<Mat, vmi> res = {make_id(n), vmi(n)};
    while (p) {
        if (p & 1) res = res * A;
        A = A * A;
        p >>= 1;
    }
    return res;
}

template<int SIG = 2> struct AC {
    struct Node {
        AR<int, SIG> to{};
        int link = 0, terminal = 0;
        bool end = false;
        vector<pi> ends;
    };
    V<Node> d{{}};
    AC(const V<string>& v) {
        for (int i = 0; i < v.size(); ++i) ins(v[i], i);
        push_links();
    }
    void ins(const string& s, int id) {
        int v = 0;
        for (char c : s) {
            int x = c == 'L';
            if (!d[v].to[x]) d[v].to[x] = d.size(), d.emplace_back();
            v = d[v].to[x];
        }
        d[v].end = true;
        d[v].ends.emplace_back(id, s.size());
    }
    void push_links() {
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            int L = d[v].link;
            d[v].terminal = d[L].end ? L : d[L].terminal;
            for (auto& p : d[d[v].terminal].ends) d[v].ends.pb(p);
            rep(c, SIG) {
                int u = d[v].to[c];
                if (!u) continue;
                int j = d[v].link;
                while (j && !d[j].to[c]) j = d[j].link;
                d[u].link = v ? d[j].to[c] : 0;
                q.push(u);
            }
            if (v) rep(c, SIG) if (!d[v].to[c])
                d[v].to[c] = d[d[v].link].to[c];
        }
    }
};

int solve(ll N, int K, int X, int Y, int W1, int W2, int L1, int L2, vector<string>& S) {
    mi w = mi(W1) / mi(W2);
    mi l = mi(L1) / mi(L2);

    AC<2> ac(S);
    int n = ac.d.size();
    V<vmi> A(2 * n, vmi(2 * n));
    rep(i, n) {
        rep(c, 2) {
            int nxt = ac.d[i].to[c];
            bool flip = ac.d[nxt].ends.size() & 1;
            int u = i + (c ? n : 0), v = nxt + (flip ? n : 0);
            A[u][v] += (c ? (1 - w) : w);
        }
    }

    vmi mu(2 * n);
    rep(i, n) {
        mu[i] = X * w - Y * (1 - w);
        mu[i + n] = X * l - Y * (1 - l);
    }

    auto [mat, vec] = mpow({A, mu}, N);
    return int(vec[0]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        ll N; int K, X, Y, W1, W2, L1, L2;
        cin >> N >> K >> X >> Y >> W1 >> W2 >> L1 >> L2;
        vector<string> S(K);
        for (auto& s : S) cin >> s;
        cout << solve(N, K, X, Y, W1, W2, L1, L2, S) << '\n';
    }
    return 0;
}