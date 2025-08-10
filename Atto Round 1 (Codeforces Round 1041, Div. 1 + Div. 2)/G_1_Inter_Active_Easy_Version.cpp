/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

#ifdef Tomato
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
#else
#define bug(x...) void(0)
#endif

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

const int MXN = 1003;
int n, k;
int p[MXN], q[MXN];
bool mark[MXN];

int ask() {
    cout << "? ";
    for (int i = 1; i <= n; ++i) cout << q[i] << ' ';
    cout << endl;
    int r; cin >> r;
    return r;
}

void output_answer() {
    cout << "! ";
    for (int i = 1; i <= n; ++i) cout << p[i] << ' ';
    cout << endl;
}

void build(int i, vi opt, vi optbad) {
    fill(mark + 1, mark + n + 1, false);
    fill(q + 1, q + n + 1, 0);
    q[k] = i;
    mark[i] = true;

    for (int j = 1; j < k && !opt.empty(); ++j) {
        q[j] = opt.back(); mark[q[j]] = true; opt.pop_back();
    }
    for (int j = n; !opt.empty(); --j) {
        q[j] = opt.back(); mark[q[j]] = true; opt.pop_back();
    }
    for (int j = k + 1; !optbad.empty(); ++j) {
        q[j] = optbad.back(); mark[q[j]] = true; optbad.pop_back();
    }

    vi rem;
    for (int j = 1; j <= n; ++j)
        if (!mark[j]) rem.pb(j);

    for (int j = 1; j <= n; ++j)
        if (!q[j]) {
            q[j] = rem.back(); rem.pop_back();
        }
}

void reverse_except_k() {
    vi vec;
    for (int i = 1; i <= n; ++i)
        if (i != k) vec.pb(q[i]);
    for (int i = 1; i <= n; ++i)
        if (i != k) {
            q[i] = vec.back(); vec.pop_back();
        }
}

void solve_case() {
    input(n);
    k = (n + 1) / 4 + 1;
    print(k);

    for (int i = 1; i <= n; ++i) {
        vi opt;
        for (int j = 1; j <= n; ++j)
            if (j != i) opt.pb(j);

        while (sz(opt) > 1) {
            int szcut = sz(opt) - min((sz(opt) + 1) / 2, n - (2 * k - 1));
            vi good(opt.begin(), opt.begin() + szcut);
            vi bad(opt.begin() + szcut, opt.end());

            build(i, good, bad);
            int val = ask();
            reverse_except_k();
            val += ask();

            if (val == n - 1)
                opt = good;
            else
                opt = bad;
        }
        p[opt.back()] = i;
    }
    output_answer();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; input(T);
    while (T--) solve_case();
    return 0;
}
