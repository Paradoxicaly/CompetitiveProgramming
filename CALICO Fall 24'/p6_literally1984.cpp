/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define pb push_back

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
}

const int MAX_M = 60427;

vector<int> phi(MAX_M);
vector<vector<int>> primes(MAX_M);
vector<int> totient_sum(MAX_M);

void preprocess() {
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i < MAX_M; ++i) {
        if (phi[i] == i) {
            for (int j = i; j < MAX_M; j += i) {
                phi[j] = phi[j] * (i - 1) / i;
                primes[j].pb(i);
            }
        }
    }

    for (int i = 2; i < MAX_M; ++i) {
        totient_sum[i] = totient_sum[i - 1] + phi[i];
    }
}

int num_coprimes(int m, int M) {
    int coprime = m;
    int sz = primes[M].size();
    for (int mask = 1; mask < (1 << sz); ++mask) {
        int bits = 0, num = 1;
        for (int j = 0; j < sz; ++j) {
            if (mask & (1 << j)) {
                ++bits;
                num *= primes[M][j];
            }
        }
        coprime += (m / num) * (bits % 2 == 0 ? 1 : -1);
    }
    return coprime;
}

pair<int, int> solve(int N) {
    int l = 0, r = MAX_M - 1, M = MAX_M - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (totient_sum[m] >= N) {
            M = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    int i = N - totient_sum[M - 1];
    l = 1, r = M;
    int ans = 1;
    while (l <= r) {
        int m = (l + r) / 2;
        int cp = num_coprimes(m, M);
        if (cp >= i) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return {ans, M - ans};
}

int32_t main() {
    cincout();
    preprocess();
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        auto [x, y] = solve(N);
        cout << x << ' ' << y << '\n';
    }
    return 0;
}