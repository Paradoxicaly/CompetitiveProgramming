/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()
using ll = long long;

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

void solve() {
    string S;
    cin >> S;

    unordered_map<char, int> block_letters = {
        {'C', 2}, {'A', 1}, {'L', 1}, {'I', 1}, {'O', 1}
    };

    unordered_map<char, char> rotations = {
        {'U', 'C'}, {'N', 'C'},
        {'H', 'I'}
    };

    unordered_map<char, int> freq;
    for (char c : S) {
        if (rotations.count(c)) {
            freq[rotations[c]]++;
        } else {
            freq[c]++;
        }
    }

    int sets_required = 0;
    bool possible = true;

    for (auto [letter, count] : freq) {
        if (block_letters.count(letter)) {
            int needed = (count + block_letters[letter] - 1) / block_letters[letter];
            sets_required = max(sets_required, needed);
        } else {
            possible = false;
            break;
        }
    }

    cout << (possible ? sets_required : -1) << '\n';
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}