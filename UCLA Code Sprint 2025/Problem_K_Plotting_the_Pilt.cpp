/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;
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

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MX = 2e5 + 5;

void solve() {
    int R, C, d;
    cin >> R >> C >> d;
    vector<vector<int>> A(R, vector<int>(C));
    rep(i, R) rep(j, C) cin >> A[i][j];

    vector<vector<int>> k(R, vector<int>(C));
    rep(i, R) rep(j, C) k[i][j] = A[i][j] / d;

    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    vector<string> ans(R, string(C, ' '));
    rep(i, R) {
        rep(j, C) {
            int m = INT_MAX;
            rep(dir, 4) {
                int ni = i + di[dir], nj = j + dj[dir];
                if (ni >= 0 && ni < R && nj >= 0 && nj < C)
                    m = min(m, k[ni][nj]);
            }
            int df = k[i][j] - m;
            if (df <= 0) ans[i][j] = ' ';
            else if (df == 1) ans[i][j] = '+';
            else if (df == 2) ans[i][j] = 'X';
            else ans[i][j] = '#';
        }
    }

    rep(i, R) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}