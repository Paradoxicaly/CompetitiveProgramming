/*
Tomato_Cultivator
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

const int MOD = 1e9 + 7;

static const int MMAX = 1000000 + 5;
int spf[MMAX], mu[MMAX];

void sieve() {
    vector<int> p;
    mu[1] = 1;
    for (int i = 2; i < MMAX; ++i) spf[i] = 0;
    for (int i = 2; i < MMAX; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            p.pb(i);
            mu[i] = -1;
        }
        for (int q : p) {
            ll x = 1LL * q * i;
            if (x >= MMAX) break;
            spf[x] = q;
            if (q == spf[i]) { mu[x] = 0; break; }
            else mu[x] = -mu[i];
        }
    }
}

inline void uniqp(int x, vi& pr) {
    pr.clear();
    while (x > 1) {
        int p = spf[x];
        pr.pb(p);
        while (x % p == 0) x /= p;
    }
}

inline ll copcnt(int v, const vi& pr, const vi& mult) {
    int k = sz(pr);
    ll res = 0;
    for (int mask = 0; mask < (1<<k); ++mask) {
        int d = 1;
        for (int i = 0; i < k; ++i) if (mask & (1<<i)) d *= pr[i];
        if (mu[d]) res += (ll)mu[d] * mult[d];
    }
    return res;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;
    vi a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    static vi cnt; cnt.assign(m+1, 0);
    static vi head; head.assign(m+1, 0);
    vi nxt(n+1, 0);

    vi ones;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 1) ones.pb(i);
        else {
            if (a[i] <= m) {
                cnt[a[i]]++;
                nxt[i] = head[a[i]];
                head[a[i]] = i;
            }
        }
    }

    int c1 = sz(ones);
    if (c1 >= 4) { cout << ones[0] << ' ' << ones[1] << ' ' << ones[2] << ' ' << ones[3] << '\n'; return; }
    if (c1 == 3) {
        int o = -1;
        for (int v = 2; v <= m && o == -1; ++v) if (head[v]) o = head[v];
        if (o == -1) { cout << 0 << '\n'; return; }
        cout << ones[0] << ' ' << ones[1] << ' ' << ones[2] << ' ' << o << '\n'; return;
    }
    if (c1 == 2) {
        int o1 = -1, o2 = -1;
        for (int v = 2; v <= m && (o1 == -1 || o2 == -1); ++v)
            for (int it = head[v]; it && (o1 == -1 || o2 == -1); it = nxt[it])
                (o1 == -1 ? o1 : o2) = it;
        if (o1 == -1 || o2 == -1) { cout << 0 << '\n'; return; }
        cout << ones[0] << ' ' << o1 << ' ' << ones[1] << ' ' << o2 << '\n'; return;
    }

    vi vals;
    for (int v = 2; v <= m; ++v) if (cnt[v] > 0) vals.pb(v);

    vi mult(m+1, 0);
    for (int d = 1; d <= m; ++d) if (mu[d]) for (int x = d; x <= m; x += d) mult[d] += cnt[x];

    auto popi = [&](int val)->int { int id = head[val]; if (id) head[val] = nxt[id]; return id; };
    auto pushi = [&](int val, int id)->void { nxt[id] = head[val]; head[val] = id; };
    auto updm = [&](int val, int delta)->void {
        if (val == 1) return;
        vi pr; uniqp(val, pr);
        int k = sz(pr);
        for (int mask = 0; mask < (1<<k); ++mask) {
            int d = 1;
            for (int i = 0; i < k; ++i) if (mask & (1<<i)) d *= pr[i];
            mult[d] += delta;
        }
    };
    auto findp = [&]()->pii {
        vi pr;
        for (int v : vals) if (cnt[v] > 0) {
            uniqp(v, pr);
            if (copcnt(v, pr, mult) > 0)
                for (int w : vals) if (cnt[w] > 0 && w != v && gcd(v,w) == 1) return {v,w};
        }
        return {-1,-1};
    };
    auto geti = [&](int val, int f1, int f2)->int {
        for (int it = head[val]; it; it = nxt[it]) if (it != f1 && it != f2) return it;
        return 0;
    };

    if (c1 == 1) {
        auto p1 = findp();
        if (p1.fi == -1) { cout << 0 << '\n'; return; }
        int v1 = p1.fi, v2 = p1.se;
        int i1 = popi(v1), i2 = popi(v2), ix = 0;
        for (int v : vals) if (head[v] && (ix = head[v]) && ix != i1 && ix != i2) break;
        if (!ix || ix == i1 || ix == i2) for (int i = 1; i <= n; ++i) if (a[i] != 1 && i != i1 && i != i2) { ix = i; break; }
        if (!ix || ix == i1 || ix == i2) { cout << 0 << '\n'; return; }
        cout << ones[0] << ' ' << ix << ' ' << i1 << ' ' << i2 << '\n'; return;
    }

    auto p1 = findp();
    if (p1.fi == -1) { cout << 0 << '\n'; return; }
    int vA = p1.fi, vB = p1.se;
    int iA = popi(vA), iB = popi(vB);
    cnt[vA]--; cnt[vB]--;
    updm(vA, -1); updm(vB, -1);

    auto p2 = findp();
    if (p2.fi != -1) {
        int vC = p2.fi, vD = p2.se;
        int iC = popi(vC), iD = popi(vD);
        cout << iA << ' ' << iB << ' ' << iC << ' ' << iD << '\n';
        return;
    }

    cnt[vA]++; cnt[vB]++; updm(vA, +1); updm(vB, +1); pushi(vA, iA); pushi(vB, iB);

    int valA = a[iA], valB = a[iB];
    vi prA, prB; uniqp(valA, prA); uniqp(valB, prB);
    ll copB = copcnt(valB, prB, mult);

    int ix = 0, iy = 0;
    for (int w : vals) if (cnt[w] > 0 && gcd(valA, w) == 1) {
        int need = (w == valB ? 2 : 1);
        if (cnt[w] >= need) {
            int candx = geti(w, iB, 0);
            if (!candx) continue;
            int valX = a[candx];
            ll forbid = 0;
            if (gcd(valB, valA) == 1) forbid++;
            if (gcd(valB, valX) == 1) forbid++;
            if (copB - forbid <= 0) continue;
            int candy = 0;
            for (int w2 : vals) if (cnt[w2] > 0 && gcd(valB, w2) == 1) {
                int avail = cnt[w2];
                if (w2 == valA) avail--;
                if (w2 == valX) avail--;
                if (avail > 0 && (candy = geti(w2, iA, candx))) break;
            }
            if (candy) { ix = candx; iy = candy; break; }
        }
    }

    if (ix && iy) cout << iA << ' ' << ix << ' ' << iB << ' ' << iy << '\n';
    else cout << 0 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    int T; cin >> T;
    while (T--) solve();
}
