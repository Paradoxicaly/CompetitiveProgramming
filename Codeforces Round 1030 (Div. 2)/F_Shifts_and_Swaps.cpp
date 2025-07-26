/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i = 0; i < (n); i++)

#ifdef Tomato
template <typename T>
ostream& operator<<(ostream &o, vector<T> v) {
    o << "{"; int f = 0;
    for (auto &x : v) o << (f++ ? " " : "") << x;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m\n";
}
#define bug(x...) bug__(32, x)
#else
#define bug(...) void(0)
#endif

int minRotation(vector<int> s) {
    int n = sz(s);
    s.resize(2*n);
    rep(i,n) s[n+i] = s[i];
    int a = 0;
    rep(b,n) {
        rep(i,n) {
            if (a+i == b || s[a+i] < s[b+i]) {
                b += max(0, i-1);
                break;
            }
            if (s[a+i] > s[b+i]) {
                a = b;
                break;
            }
        }
    }
    return a;
}

vector<int> getf(int n, int m, vector<int> a) {
    vector<vector<int>> pos(m);
    rep(i,n) pos[a[i]].pb(i);
    vector<int> L(n,-1), R(n,-1);
    rep(i, sz(pos[0])-1) {
        R[pos[0][i]] = pos[0][i+1];
        L[pos[0][i+1]] = pos[0][i];
    }
    R[pos[0].back()] = pos[0][0];
    L[pos[0][0]] = pos[0].back();
    for(int v = 1; v < m; v++) {
        int sz1 = sz(pos[v-1]);
        int sz2 = sz(pos[v]);
        rep(i, sz1) {
            int x = pos[v-1][i];
            int y = (i+1==sz1 ? pos[v-1][0]+n : pos[v-1][i+1]) % n;
            int vl = int(lower_bound(all(pos[v]), x) - pos[v].begin());
            int vr = int(lower_bound(all(pos[v]), y) - pos[v].begin());
            if ((i+1)==sz1) vr += sz2;
            int cur = L[y];
            for(int j=vl; j<vr; j++) {
                int z = pos[v][j%sz2];
                R[cur] = z;  L[z] = cur;
                R[z] = y;    L[y] = z;
                cur = z;
            }
        }
    }
    vector<int> b(n);
    for(int i=0, j=0; i<n; i++, j=R[j]) {
        b[i] = a[j];
    }
    rotate(b.begin(), b.begin() + minRotation(b), b.end());
    return b;
}

void solve(){
    int n, m;
    cin >> n >> m;
    vi a(n), b(n);
    rep(i,n){ cin >> a[i]; --a[i]; }
    rep(i,n){ cin >> b[i]; --b[i]; }
    auto A = getf(n,m,a);
    auto B = getf(n,m,b);
    cout << (A==B ? "YES\n" : "NO\n");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}