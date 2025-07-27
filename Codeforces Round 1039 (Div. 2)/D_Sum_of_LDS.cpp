/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define all(x) begin(x), end(x)

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

void solve() {
    int n;
    input(n);
    vi p(n);
    for(int i = 0; i < n; i++) cin >> p[i];
    ll ans = (ll)n * (n + 1) / 2;
    for(int i = 0; i + 1 < n; i++){
        if(p[i] > p[i+1]){
            ans += (ll)(i+1) * (n - (i+1));
        }
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    input(T);
    while(T--) solve();
    return 0;
}