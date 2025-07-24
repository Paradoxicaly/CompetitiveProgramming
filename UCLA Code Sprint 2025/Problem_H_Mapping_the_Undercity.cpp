/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define fi first
#define se second
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

const ll MOD = 1'000'000'007;

ll mod_pow(ll base, ll exp) {
    ll res = 1 % MOD;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

void solve() {
    int N;
    if (!(cin >> N)) {
        cout << 0 << '\n';
        return;
    }

    vector<ll> a(N + 1), b(N + 1);
    for (int i = 1; i <= N; ++i) cin >> a[i];
    for (int i = 1; i <= N; ++i) cin >> b[i];

    ll D = a[2];
    if (b[1] != D || D > N - 1 || a[1] != 0 || b[2] != 0) {
        cout << 0 << '\n';
        return;
    }

    vector<char> path_present(D + 1, 0);
    vector<vector<int>> off_depths(D + 1);

    for (int v = 1; v <= N; ++v) {
        ll av = a[v], bv = b[v];

        if (av + bv < D || ((av + bv - D) & 1LL) || ((av - bv + D) & 1LL)) {
            cout << 0 << '\n';
            return;
        }

        ll h = (av + bv - D) / 2;
        ll s = (av - bv + D) / 2;

        if (s < 0 || s > D) {
            cout << 0 << '\n';
            return;
        }

        if (h == 0) {
            if (path_present[s]) {
                cout << 0 << '\n';
                return;
            }
            path_present[s] = 1;
        } else {
            off_depths[s].pb((int)h);
        }
    }

    if (!all_of(all(path_present), [](char c) { return c; })) {
        cout << 0 << '\n';
        return;
    }

    ll ans = 1;
    rep(s, D + 1) {
        if (off_depths[s].empty()) continue;
        unordered_map<int, int> freq;
        int max_depth = 0;
        for (int h : off_depths[s]) {
            ++freq[h];
            max_depth = max(max_depth, h);
        }

        ll pap = 1;
        rng(d, 1, max_depth + 1) {
            ll cnt = freq.count(d) ? freq[d] : 0;
            if (cnt) {
                if (pap == 0) {
                    cout << 0 << '\n';
                    return;
                }
                ans = ans * mod_pow(pap, cnt) % MOD;
            }
            pap = cnt;
        }
    }

    cout << ans % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}