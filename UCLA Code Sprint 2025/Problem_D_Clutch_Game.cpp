/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
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

int T, M;
vector<ld> P2, P3, Z2, Z3;

map<tuple<int, int, int, int>, ld> memo;

ld dfs(int time, int ps, int zs, int who) {
    if (time == 0) return ps > zs ? 1.0 : 0.0;

    auto key = make_tuple(time, ps, zs, who);
    if (memo.count(key)) return memo[key];

    ld res = 0;
    const vector<ld> &prob2 = (who == 0 ? P2 : Z2);
    const vector<ld> &prob3 = (who == 0 ? P3 : Z3);

    for (int i = 0; i < min(M, time); ++i) {
        ld miss = 1 - prob2[i] - prob3[i];

        if (who == 0) {
            ld option = 0;
            option += prob2[i] * dfs(time - i - 1, ps + 2, zs, 1);
            option += prob3[i] * dfs(time - i - 1, ps + 3, zs, 1);
            option += miss     * dfs(time - i - 1, ps, zs, 1);
            res = max(res, option);
        } else {
            ld option = 0;
            option += prob2[i] * dfs(time - i - 1, ps, zs + 2, 0);
            option += prob3[i] * dfs(time - i - 1, ps, zs + 3, 0);
            option += miss     * dfs(time - i - 1, ps, zs, 0);
            res = min(res == 0 ? 1.0 : res, option);
        }
    }

    return memo[key] = res;
}

void solve() {
    cin >> T >> M;
    P2.resize(M), P3.resize(M), Z2.resize(M), Z3.resize(M);
    rep(i, M) cin >> P2[i];
    rep(i, M) cin >> P3[i];
    rep(i, M) cin >> Z2[i];
    rep(i, M) cin >> Z3[i];

    memo.clear();
    cout << fixed << setprecision(6) << dfs(T, 0, 0, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}