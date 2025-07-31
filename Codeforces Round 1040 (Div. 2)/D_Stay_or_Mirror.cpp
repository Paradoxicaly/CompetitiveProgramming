/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i,n) for (int i = 0; i < (n); ++i)

template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}
template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a; (cout << ... << (cout << ' ', b)); cout << '\n';
}

void solve(){
    int n;
    input(n);
    vi p(n);
    rep(i,n) input(p[i]);

    vi l(n), r(n), BIT(n+1,0);
    auto add = [&](int i){
        for(; i <= n; i += i & -i) BIT[i]++;
    };
    auto sum = [&](int i){
        int s = 0;
        for(; i > 0; i -= i & -i) s += BIT[i];
        return s;
    };
    rep(i,n){
        l[i] = sum(n) - sum(p[i]);
        add(p[i]);
    }
    fill(BIT.begin(), BIT.end(), 0);
    for(int i = n-1; i >= 0; --i){
        r[i] = sum(p[i] - 1);
        add(p[i]);
    }

    ll base = 0;
    rep(i,n) base += l[i];
    ll ans = base;
    rep(i,n){
        ll D = ll(n - 1 - i) - (l[i] + r[i]);
        if (D < 0) ans += D;
    }
    print(ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while(T--) solve();
    return 0;
}