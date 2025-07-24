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

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    rep(i, N) cin >> A[i];

    K--;
    if (K == 0) {
        cout << "YES\n";
        return;
    }

    vector<int> V = A;
    nth_element(all(V), V.begin() + (K - 1));
    int thresh = V[K - 1];

    vector<int> freq = {0};
    vector<int> vals;

    for (int v : A) {
        if (v < thresh) {
            vals.pb(v);
            freq.pb(0);
        } else if (v == thresh) {
            freq.back()++;
        }
    }

    bool good = true;
    rep(i, sz(vals)) {
        if (vals[i] != vals[sz(vals) - 1 - i]) {
            good = false;
            break;
        }
    }

    int cnt = sz(vals);
    for (int i = 0, j = sz(freq) - 1; i <= j; ++i, --j) {
        if (i == j) {
            cnt += freq[i];
        } else {
            cnt += 2 * min(freq[i], freq[j]);
        }
    }

    if (cnt < K) good = false;

    cout << (good ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}