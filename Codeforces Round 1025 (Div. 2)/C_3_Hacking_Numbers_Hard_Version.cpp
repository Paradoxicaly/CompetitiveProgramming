/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;
    cout << "mul 999999999" << endl;
    ll x;
    cin >> x;  

    cout << "digit" << endl; 
    cin >> x;

    if (n != 81) {
        cout << "add " << (n - 81) << endl;
        cin >> x;
    }

    cout << "!" << endl;
    cin >> x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
