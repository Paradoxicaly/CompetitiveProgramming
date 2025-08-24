#include <bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define endl "\n"
#define vec vector
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back
#define maxel(v) *max_element(v.begin(), v.end())
#define minel(v) *min_element(v.begin(), v.end())
#define yes cout << "YES\n";
#define m1 cout << "-1\n";
#define no cout << "NO\n";
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll mod = 1e9 + 7;
const ll mod2 = 1e9 + 9;
const ll mod3 = 998244353;
const double pi = 3.141592653589793238;
const long double EPS = 1e-9;
const int MAXN = 1e5 * 5;

template <typename T>
ostream& operator<< (ostream &os, const pair<T, T>& a){
    return os << a.fi << " " << a.se;
}
template <typename T>
istream& operator>> (istream& in, pair<T, T>& a){
    in >> a.fi >> a.se;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, const vector<T>& a){
    for (int x : a) os << x << " ";
    return os;
}
template <typename T>
istream& operator>> (istream& in, vector<pair<T, T>>& a){
    for (pair<int, int>& x : a) in >> x.fi >> x.se;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, const vector<pair<T, T>>& a){
    for (pair<int, int> x : a) os << x.fi << " " << x.se << endl;
    return os;
}
template <typename T>
istream& operator>> (istream& in, vector<T>& a){
    for (int& x : a) in >> x;
    return in;
}
template <typename T>
ostream& operator<< (ostream &os, const set<T>& a){
    for (int x : a) os << x << " ";
    return os;
}
template <typename T>
ostream& operator<< (ostream &os, const map<T, T>& a){
    for (pair<int, int> x : a) os << x.fi << " " << x.se << endl;
    return os;
}
template <typename T>
void printrb(vector<T>* rb, int n) {
    for (int u = 0; u < n; ++u) {
        for (const T& v : rb[u]) {
            cout << u << " -> " << v << '\n';
        }
    }
}
template <typename T>
void print2d(const vec<vec<T>> &vec) {
    for (const auto &row : vec) {
        for (const auto &i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    if (!(cin >> t)) return 0;
    while (t--) {
        int n; cin >> n;
        vec<ll> h(n);
        for (int i = 0; i < n; ++i) cin >> h[i];
        ll base = 0;
        for (ll x : h) base += x;
        base -= (n - 1);
        ll a = 0, b = 0;
        for (int i = 1; i < n; ++i) {
            ll w = min<ll>((ll)i, h[i]) - 2;
            if (w < 0) w = 0;
            ll c = max(b, a + w);
            a = b;
            b = c;
        }
        cout << (base - b) << endl;
    }
    return 0;
}

