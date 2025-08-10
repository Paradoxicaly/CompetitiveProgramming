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
constexpr auto min(T... a){ return std::min({a...}); }

template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

constexpr int N = 3e5 + 10;
constexpr int S = 1.1e7, SS = 2 * S;

int n, q, cnt;
int next_ptr[SS], val_ptr[SS];

struct Queue {
    int head = 0, tail = 0;

    void push(int x) {
        if (head) {
            next_ptr[tail] = ++cnt;
            val_ptr[cnt] = x;
            tail = cnt;
        } else {
            head = tail = ++cnt;
            val_ptr[cnt] = x;
        }
    }

    void pop() { head = next_ptr[head]; }
    int front() { return val_ptr[head]; }
    bool empty() const { return head == 0; }
    bool single() const { return head == tail; }
    void clear() { head = tail = 0; }
};

struct Node {
    int ls = 0, rs = 0;
    Queue fa;
    int val = 0, exit = 0;
    int size = 0, rev = 0;
} a[S];

int tot = 0, id[N];

int newNode() {
    int u = ++tot;
    a[u].exit = 2;
    return u;
}

int newLeaf() {
    int u = newNode();
    a[u].size = 1;
    return u;
}

void pushup(int u) {
    a[u].size = a[a[u].ls].size + a[a[u].rs].size;
}

void setRev(int u) {
    if (!u) return;
    a[u].rev ^= 1;
    swap(a[u].ls, a[u].rs);
}

void setTag(int u, int v) {
    a[u].fa.push(v);
}

void pushdown(int u) {
    if (a[u].rev) {
        setRev(a[u].ls);
        setRev(a[u].rs);
        a[u].rev = 0;
    }
}

int join(int x, int y) {
    int u = newNode();
    a[u].ls = x;
    a[u].rs = y;
    setTag(x, u);
    setTag(y, u);
    pushup(u);
    return u;
}

pii cut(int x) {
    pushdown(x);
    a[x].exit = 1;
    return {a[x].ls, a[x].rs};
}

int get_val(int u) {
    if (a[u].exit == 0) return 0;
    if (a[u].val != 0) return a[u].val;
    if (a[u].fa.empty()) return 0;

    while (true) {
        int res = get_val(a[u].fa.front());
        if (res) return res;
        if (a[u].fa.single()) break;
        a[u].fa.pop();
    }

    if (a[u].exit == 1) {
        a[u].exit = 0;
        a[u].fa.pop();
        a[u].fa.clear();
    }

    return 0;
}

int newTag(int x) {
    int u = ++tot;
    a[u].val = x;
    a[u].exit = 1;
    return u;
}

constexpr double ALPHA = 0.292;

bool tooHeavy(int sx, int sy) {
    return sy < ALPHA * (sx + sy);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;

    if (tooHeavy(a[x].size, a[y].size)) {
        auto [u, v] = cut(x);
        if (tooHeavy(a[v].size + a[y].size, a[u].size)) {
            auto [z, w] = cut(v);
            return merge(merge(u, z), merge(w, y));
        } else {
            return merge(u, merge(v, y));
        }
    } else if (tooHeavy(a[y].size, a[x].size)) {
        auto [u, v] = cut(y);
        if (tooHeavy(a[u].size + a[x].size, a[v].size)) {
            auto [z, w] = cut(u);
            return merge(merge(x, z), merge(w, v));
        } else {
            return merge(merge(x, u), v);
        }
    }

    return join(x, y);
}

pii split(int x, int k) {
    if (!x) return {0, 0};
    if (!k) return {0, x};
    if (k == a[x].size) return {x, 0};

    auto [u, v] = cut(x);
    if (k <= a[u].size) {
        auto [w, z] = split(u, k);
        return {w, merge(z, v)};
    } else {
        auto [w, z] = split(v, k - a[u].size);
        return {merge(u, w), z};
    }
}

int find(int u, int k) {
    if (a[u].size == 1) return u;
    pushdown(u);
    if (k <= a[a[u].ls].size) return find(a[u].ls, k);
    return find(a[u].rs, k - a[a[u].ls].size);
}

int build(int len) {
    if (len == 1) return newLeaf();
    int x = build(len / 2);
    int y = build(len - len / 2);
    return join(x, y);
}

void solve() {
    input(n, q);
    int root = build(n);
    int last = 0;

    rep(i, q) {
        int op;
        input(op);

        if (op == 1) {
            int p;
            input(p);
            p = (p + last - 1) % n + 1;
            auto [A, B] = split(root, p);
            setTag(A, id[i + 1] = newTag(i + 1));
            root = merge(A, B);
        } else if (op == 2) {
            int p;
            input(p);
            p = (p + last - 1) % n + 1;
            auto [A, B] = split(root, p);
            setRev(A);
            root = merge(A, B);
        } else if (op == 3) {
            int x;
            input(x);
            x = (x + last - 1) % q + 1;
            a[id[x]].exit = 0;
        }

        int pos;
        input(pos);
        pos = (pos + last - 1) % n + 1;
        int u = find(root, pos);
        print(last = get_val(u));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}
