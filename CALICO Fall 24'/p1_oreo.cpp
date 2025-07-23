/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

void draw_cookie(const string& S) {
    const string O_output = "[###OREO###]";
    const string RE_output = "[--------]";
    const string empty_output = "";

    int i = 0;
    while (i < (int)S.length()) {
        if (i + 1 < (int)S.length() && S.substr(i, 2) == "RE") {
            cout << RE_output << '\n';
            i += 2;
        } else if (S[i] == 'O') {
            cout << O_output << '\n';
            i++;
        } else if (S[i] == '&') {
            cout << empty_output << '\n';
            i++;
        } else {
            cerr << "Invalid input detected: " << S[i] << '\n';
            return;
        }
    }
}

void solve() {
    string S;
    getline(cin, S);
    draw_cookie(S);
}

int main() {
    cincout();
    int T;
    cin >> T;
    cin.ignore(); // important to handle getline after cin
    while (T--) solve();
    return 0;
}