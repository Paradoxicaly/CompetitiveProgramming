/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

#define fi first
#define se second
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rng(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

template<class T> bool chmin(T& a, T b) { return (b < a ? a = b, true : false); }
template<class T> bool chmax(T& a, T b) { return (b > a ? a = b, true : false); }

mt19937 rnd(time(0));

template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
    return os << p.first << ' ' << p.second << '\n';
}

template<typename T, typename = void>
struct is_container : false_type {};

template<typename T>
struct is_container<T, void_t<
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end())
>> : true_type {};

template<typename T>
void print(const T& element) {
    if constexpr (is_container<T>::value) {
        for (const auto& e : element) print(e);
        cout << '\n';
    } else {
        cout << element << ' ';
    }
}

void solve() {
    int n;
    cin >> n;
    vector<ll> p(n), s(n);
    rep(i, n) cin >> p[i];
    rep(i, n) cin >> s[i];

    rep(i, n - 1) {
        if (p[i] % p[i + 1]) {
            cout << "NO\n";
            return;
        }
    }

    rep(i, n - 1) {
        if (s[i + 1] % s[i]) {
            cout << "NO\n";
            return;
        }
    }

    if (p[n - 1] != s[0]) {
        cout << "NO\n";
        return;
    }

    vector<ll> tmp(n);
    rep(i, n) tmp[i] = lcm(p[i], s[i]);

    rng(i, 1, n) {
        if (p[i] != __gcd(p[i - 1], tmp[i])) {
            cout << "NO\n";
            return;
        }
    }

    for (int i = n - 2; i >= 0; --i) {
        if (s[i] != __gcd(s[i + 1], tmp[i])) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}