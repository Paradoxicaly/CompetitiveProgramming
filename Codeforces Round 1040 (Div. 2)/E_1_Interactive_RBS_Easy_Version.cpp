/*
 Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

int ask(const vi& idx) {
    cout << "? " << idx.size();
    for (int x : idx) cout << " " << x;
    cout << "\n" << flush;
    int r;
    cin >> r;
    if (r < 0) exit(0);
    return r;
}

void solve() {
    int n;
    cin >> n;
    vi d(n+1, 0);
    for (int i = 2; i <= n; i++) {
        d[i] = ask({1, i, 1});
    }
    int j = -1;
    for (int i = 2; i <= n; i++) {
        if (d[i] == 1) {
            j = i;
            break;
        }
    }
    char s1;
    if (j == -1) {
        s1 = '(';
    } else {
        int r = ask({1, j, j});
        s1 = (r == 1 ? '(' : ')');
    }

    string s(n, '?');
    s[0] = s1;
    for (int i = 2; i <= n; i++) {
        s[i-1] = (d[i] == 0
                  ? s1
                  : (s1 == '(' ? ')' : '('));
    }

    cout << "! " << s << "\n" << flush;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}