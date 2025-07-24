/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
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

struct DSU {
    vector<int> f, siz;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n) {
        f.resize(n);
        iota(all(f), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i, n) {
        cin >> a[i];
        --a[i];
    }

    DSU fl(n + 1), fr(n + 1);
    vector<int> cnt(n), p(n);
    rep(i, n) cnt[a[i]]++;
    rng(i, 1, n) cnt[i] += cnt[i - 1];
    rep(i, n) p[--cnt[a[i]]] = i;

    int ans = 0, mn = n;
    reverse(all(p));
    for (int i : p) {
        rep(_, 2) {
            int x = fl.find(i + 1);
            if (x) {
                fl.merge(x - 1, x);
                mn = min(mn, a[x - 1]);
            }
            x = fr.find(i);
            if (x < n) {
                fr.merge(x + 1, x);
                mn = min(mn, a[x]);
            }
        }
        ans = max(ans, a[i] - mn);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}