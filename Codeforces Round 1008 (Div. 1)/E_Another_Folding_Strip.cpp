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

const ll MOD = 998244353;
int n;
ll a[200200];
ll Answer;

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    solve(l, mid);
    solve(mid + 1, r);
    vector<ll> vl[2], vr[2];
    
    rep(b, 2) {
        ll vm = 0, vs = 0, vt = 0;
        for (int i = mid; i >= l; i--) {
            if ((mid - i) % 2 == b)
                vm += a[i];
            else {
                if (a[i] > vm) {
                    vs += a[i] - vm;
                    vt += vm;
                    vm = 0;
                } else {
                    vt += a[i];
                    vm -= a[i];
                }
            }
            vl[b].pb(vs);
            Answer = (Answer + vt % MOD * (r - mid)) % MOD;
        }
        vm = 0;
        vs = 0;
        vt = 0;
        rng(i, mid + 1, r + 1) {
            if ((i - mid) % 2 == b)
                vm += a[i];
            else {
                if (a[i] > vm) {
                    vs += a[i] - vm;
                    vt += vm;
                    vm = 0;
                } else {
                    vt += a[i];
                    vm -= a[i];
                }
            }
            vr[b].pb(vs);
            Answer = (Answer + vt % MOD * (mid - l + 1)) % MOD;
        }
    }
    
    rep(i, 2) {
        sort(all(vl[i]));
        sort(all(vr[i ^ 1]));
        ll sum = 0;
        int p = 0;
        for (auto x : vr[i ^ 1]) {
            while (p < sz(vl[i]) && vl[i][p] < x)
                sum += vl[i][p++];
            Answer = (Answer + sum + x % MOD * (sz(vl[i]) - p)) % MOD;
        }
    }
}

void solve() {
    cin >> n;
    rng(i, 1, n + 1)
        cin >> a[i];
    Answer = 0;
    solve(1, n);
    ll Tot = 0;
    rng(i, 1, n + 1)
        Tot = (Tot + 1LL * i * (n + 1 - i) % MOD * a[i]) % MOD;
    cout << (Tot - Answer + MOD) % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}