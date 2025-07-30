/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        int n;
        cin >> n;
        vector<int> p(n), q(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) cin >> q[i];

        // precompute 2^k mod MOD
        vector<ll> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; i++){
            pow2[i] = (pow2[i-1] * 2) % MOD;
        }

        // prefix‐max indices for p and q
        vector<int> Pidx(n), Qidx(n);
        int mp = 0, mq = 0;
        for (int i = 0; i < n; i++){
            if (p[i] > p[mp]) mp = i;
            if (q[i] > q[mq]) mq = i;
            Pidx[i] = mp;
            Qidx[i] = mq;
        }

        // compute r
        vector<ll> r(n);
        for (int i = 0; i < n; i++){
            int jv = Pidx[i];
            int kv = Qidx[i];
            int big1 = p[jv], small1 = q[i - jv];
            int big2 = q[kv], small2 = p[i - kv];
            int big, small;
            if (big1 > big2){
                big = big1; small = small1;
            } else if (big2 > big1){
                big = big2; small = small2;
            } else {
                big = big1;
                small = max(small1, small2);
            }
            r[i] = (pow2[big] + pow2[small]) % MOD;
        }

        // output
        for (int i = 0; i < n; i++){
            cout << r[i] << (i+1==n? '\n' : ' ');
        }
    }
    return 0;
}