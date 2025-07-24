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

const int MOD = 1e9 + 7;

map<pii, int> monkey_at;
map<pii, char> mirror;
vector<pii> monkey_pos;

unordered_map<char, array<int, 4>> refl = {
    {'/', {1, 0, 3, 2}},
    {'\\', {3, 2, 1, 0}}
};

int dx[4] = {0, 1, 0, -1}; // N, E, S, W
int dy[4] = {1, 0, -1, 0};

int decrypt(int x, int sum) {
    return (x + sum) % MOD;
}

int zap(int id, int dir) {
    int x = monkey_pos[id].fi, y = monkey_pos[id].se;
    while (true) {
        x += dx[dir];
        y += dy[dir];
        pii pos = {x, y};
        if (monkey_at.count(pos)) return monkey_at[pos];
        if (!mirror.count(pos)) continue;
        char m = mirror[pos];
        dir = refl[m][dir];
    }
    return -1;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    monkey_pos.resize(n + 1);
    rep(i, n) {
        int x, y; cin >> x >> y;
        monkey_pos[i + 1] = {x, y};
        monkey_at[{x, y}] = i + 1;
    }

    rep(i, m) {
        int x, y; char c;
        cin >> x >> y >> c;
        mirror[{x, y}] = c;
    }

    int sum = 0;
    rep(_, q) {
        int type; cin >> type;
        if (type == 1) {
            int i, x, y; cin >> i >> x >> y;
            x = decrypt(x, sum);
            y = decrypt(y, sum);
            monkey_at.erase(monkey_pos[i]);
            monkey_pos[i] = {x, y};
            monkey_at[{x, y}] = i;
        } else if (type == 2) {
            int x, y; char c;
            cin >> x >> y >> c;
            x = decrypt(x, sum);
            y = decrypt(y, sum);
            if (c == '.') {
                mirror.erase({x, y});
            } else {
                mirror[{x, y}] = c;
            }
        } else if (type == 3) {
            int i; char d; cin >> i >> d;
            int dir = (d == 'N' ? 0 : d == 'E' ? 1 : d == 'S' ? 2 : 3);
            int result = zap(i, dir);
            cout << result << '\n';
            if (result != -1) sum = (sum + result) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}