/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
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
#else
#define bug(x...) void(0)
#endif

const int N = 200200;
int n;
ll a[N];
ll sr[N];
ll b[N];
int m;
ll suf[N];
ll bst[N];
int bstSz;
ll curAns[N];
int curSz;

const ll INF = (ll)1e18;

struct Item {
    ll x;

    Item() : x(-INF) {}
    Item(ll _x) : x(_x) {}

    Item& operator += (const Item &I) {
        x = max(x, I.x);
        return *this;
    }
    Item operator + (const Item &I) const {
        return Item(*this) += I;
    }
};

template<typename T, bool right_assoc> struct Stack {
    vector<T> vals, mins;

    Stack() : vals(), mins({T()}) {}

    void push(T x) {
        vals.pb(x);
        if constexpr (right_assoc)
            mins.pb(x + mins.back());
        else
            mins.pb(mins.back() + x);
    }
    T pop() {
        mins.pop_back();
        T x = vals.back();
        vals.pop_back();
        return x;
    }
    T get() const {
        return mins.back();
    }
    bool empty() const {
        return vals.empty();
    }
    void clear() {
        vals = vector<T>();
        mins = vector<T>({T()});
    }
    int size() const {
        return (int)vals.size();
    }
};

template<typename T> struct Queue {
    Stack<T, false> A;
    Stack<T, true> B;

    Queue() : A(), B() {}

    void push(T x) {
        A.push(x);
    }
    T pop() {
        if (B.empty()) {
            while(!A.empty()) {
                B.push(A.pop());
            }
        }
        assert(!B.empty());
        return B.pop();
    }
    T get() {
        return B.get() + A.get();
    }
    bool empty() const {
        return A.empty() && B.empty();
    }
    void clear() {
        A.clear();
        B.clear();
    }
    int size() const {
        return A.size() + B.size();
    }
};

void trySolveWithMax(ll mx) {
    m = 0;
    rep(i, n) if (a[i] <= mx)
        b[m++] = a[i];
    suf[m] = 0;
    for (int i = m - 1; i >= 0; i--)
        suf[i] = suf[i + 1] + b[i];
    ll want = 2 * mx + 1;
    int l = 0, r = 0;
    Queue<Item> Q;
    curSz = 0;
    while(l < m) {
        while(r < m && suf[r] >= want) {
            Q.push(Item(b[r++]));
        }
        if (Q.empty()) return;
        ll x = Q.get().x;
        while(b[l] != x) {
            l++;
            Q.pop();
        }
        Q.pop();
        l++;
        curAns[curSz++] = x;
        want -= x;
    }
    if (want > 0) return;
    int pos = 0;
    while(pos < bstSz && pos < curSz && bst[pos] == curAns[pos]) pos++;
    if (pos >= bstSz || (pos < curSz && curAns[pos] > bst[pos])) {
        bstSz = curSz;
        rep(i, bstSz)
            bst[i] = curAns[i];
    }
}

void solve() {
    cin >> n;
    rep(i, n) {
        cin >> a[i];
        sr[i] = a[i];
    }
    sort(sr, sr + n);
    reverse(sr, sr + n);
    bstSz = -1;
    bst[0] = -1;
    rep(k, min(n, 66)) if (k == 0 || sr[k] != sr[k - 1]) {
        trySolveWithMax(sr[k]);
    }
    cout << bstSz << '\n';
    rep(i, bstSz)
        cout << bst[i] << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}