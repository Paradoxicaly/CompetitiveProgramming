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
    int N;
    cin >> N;
    vector<ll> A(N);
    rep(i, N) cin >> A[i];
    
    ll tot = accumulate(all(A), 0LL);
    if (tot & 1) {
        cout << -1 << '\n';
        return;
    }

    ll cur_sum = 0;
    int mid = -1;
    while (cur_sum < tot / 2) {
        mid++;
        cur_sum += A[mid];
    }

    assert(cur_sum >= tot / 2);
    if (cur_sum == tot / 2) {
        cout << 1 << '\n';
        rep(i, N) cout << A[i] << " \n"[i + 1 == N];
        return;
    }

    assert(cur_sum > tot / 2);
    assert(mid != -1);
    if (A[mid] * 2 > tot) {
        cout << -1 << '\n';
        return;
    }

    vector<ll> B(N);
    ll cnt = cur_sum - tot / 2;
    rep(i, mid) {
        ll v = min(A[i], cnt);
        B[i] += v;
        B[mid] += v;
        A[i] -= v;
        A[mid] -= v;
        cnt -= v;
    }

    assert(cnt == 0);
    cout << 2 << '\n';
    rep(i, N) cout << A[i] << " \n"[i + 1 == N];
    rep(i, N) cout << B[i] << " \n"[i + 1 == N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}