#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int k = -1;
    bool ok = true;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x != -1) {
            if (k == -1) k = x;
            else if (x != k) ok = false;
        }
    }
    if (!ok) {
        cout << "NO\n";
    } else if (k == -1) {
        cout << "YES\n";
    } else if (k == 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}

