/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

ll countUwuPairs(const string &s) {
    ll totalU = 0;
    for (char c : s) if (c == 'u') totalU++;

    ll totalPairs = totalU * (totalU - 1) / 2;

    ll invalidPairs = 0, curr = 0;
    for (char c : s) {
        if (c == 'w') {
            invalidPairs += curr * (curr - 1) / 2;
            curr = 0;
        } else if (c == 'u') {
            curr++;
        }
    }
    invalidPairs += curr * (curr - 1) / 2;

    return totalPairs - invalidPairs;
}

void solve() {
    string s;
    cin >> s;
    cout << countUwuPairs(s) << '\n';
}

int main() {
    cincout();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}