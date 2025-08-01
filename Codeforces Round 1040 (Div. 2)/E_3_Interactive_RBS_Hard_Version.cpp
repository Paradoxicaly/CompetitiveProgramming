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
constexpr auto min(T... a){
    return std::min({a...});
}

template<class... T>
constexpr auto max(T... a){
    return std::max({a...});
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

ll gcd(ll a, ll b) { 
    return b ? gcd(b, a % b) : a; 
}

ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    input(n);
    
    cout << "? " << n << " ";
    rng(i, 1, n + 1) {
        cout << i << " ";
    }
    cout << endl;
    
    int res;
    input(res);
    
    int open = 0;
    if (res == 0) {
        open = n;
    } else {
        int l = 0, r = n;
        while (r - l > 2) {
            int m = (r + l) / 2;
            cout << "? " << (m - l) * 2 << " ";
            rng(i, l + 1, m + 1) {
                cout << i << " ";
            }
            rng(i, l + 1, m + 1) {
                cout << i << " ";
            }
            cout << endl;
            input(res);
            
            if (res == 0) {
                cout << "? " << (r - m) * 2 << " ";
                rng(i, m + 1, r + 1) {
                    cout << i << " ";
                }
                rng(i, m + 1, r + 1) {
                    cout << i << " ";
                }
                cout << endl;
                input(res);
                
                if (res == 0) {
                    l = m - 1;
                    r = m + 1;
                } else {
                    l = m;
                }
            } else {
                r = m;
            }
        }
        
        cout << "? " << 2 << " " << l + 1 << " " << r << endl;
        input(res);
        
        if (res > 0) {
            open = l + 1;
        } else {
            open = r;
        }
    }
    
    string ans = "";
    
    vi q1(13, 0), q2(13, 0);
    q1[0] = q2[0] = 1;
    int sum1 = 1, sum2 = 3;
    
    rng(i, 1, 13) {
        int val = 0;
        while (val * (val + 1) / 2 <= sum1) {
            ++val;
        }
        q1[i] = val;
        q2[i] = val * (val + 1) / 2;
        sum1 += q2[i];
        sum2 += q1[i] * 2 + 1;
    }
    
    for (int i = 1; i <= n; i += 13) {
        cout << "? " << " " << sum2 << " ";
        rep(j, 13) {
            rep(g, q1[j]) {
                cout << open << " " << min(n, i + j) << " ";
            }
            cout << open << " ";
        }
        cout << endl;
        input(res);
        
        string tmp_ans = "";
        for (int j = 12; j >= 0; --j) {
            if (res >= q2[j]) {
                res -= q2[j];
                tmp_ans += ')';
            } else {
                tmp_ans += '(';
            }
        }
        
        for (int j = 12; j >= 0; --j) {
            ans += tmp_ans[j];
        }
    }
    
    cout << "! " << ans.substr(0, n) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}