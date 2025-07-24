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

template<class... T>
constexpr auto min(T... a){
    return std::min({a...});
}

template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
void print() { cout << '\n'; }

const int INF = 0x3f3f3f3f;

void solve() {
    int n, m;
    input(n, m);
    
    vector<vector<int>> w(n, vector<int>(n, INF));
    rep(i, n) w[i][i] = 0;
    
    rep(i, m) {
        int x, y, z;
        input(x, y, z);
        x--; y--;
        swap(x, y);
        w[x][y] = min(w[x][y], z);
    }
    
    vector<vector<int>> dis = w;
    rep(k, n) rep(i, n) rep(j, n) {
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    
    int q;
    input(q);
    while(q--) {
        int x;
        input(x);
        vector<int> a(n);
        rep(i, n) input(a[i]);
        
        string res = "";
        rep(i, n) {
            int val = a[i];
            rep(j, n) {
                val = min(val, a[j] + w[j][i]);
            }
            
            bool f = 0;
            rep(j, n) {
                if (dis[j][i] < w[j][i]) {
                    if (a[j] - x + dis[j][i] < val) {
                        f = 1;
                    }
                }
            }
            
            if (f) res += '1';
            else res += '0';
        }
        print(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}