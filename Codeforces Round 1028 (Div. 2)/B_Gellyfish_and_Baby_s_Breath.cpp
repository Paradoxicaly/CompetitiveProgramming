/*
Tomato_Cultivator
*/
 
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int MOD = 998244353;
 
template<class... T>
void input(T&... a){
    (cin >> ... >> a);
}
 
void solve() {
    int n;
    input(n);
    vector<int> p(n), q(n);
    for (int i = 0; i < n; i++) input(p[i]);
    for (int i = 0; i < n; i++) input(q[i]);
 
    static vector<ll> pow2;
    if ((int)pow2.size() < n) {
        pow2.assign(n, 0);
        pow2[0] = 1;
        for (int i = 1; i < n; i++) {
            pow2[i] = (pow2[i-1] * 2) % MOD;
        }
    }
 
    vector<int> Pval(n), Pidx(n), Qval(n), Qidx(n);
    for (int i = 0; i < n; i++) {
        if (i == 0 || p[i] > Pval[i-1]) {
            Pval[i] = p[i];
            Pidx[i] = i;
        } else {
            Pval[i] = Pval[i-1];
            Pidx[i] = Pidx[i-1];
        }
        if (i == 0 || q[i] > Qval[i-1]) {
            Qval[i] = q[i];
            Qidx[i] = i;
        } else {
            Qval[i] = Qval[i-1];
            Qidx[i] = Qidx[i-1];
        }
    }
 
    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        int pv = Pval[i], qv = Qval[i];
        ll sum;
        if (pv > qv) {
            int j = Pidx[i];
            int sec = q[i - j];
            sum = pow2[pv] + pow2[sec];
        } else if (qv > pv) {
            int k = Qidx[i];
            int sec = p[i - k];
            sum = pow2[qv] + pow2[sec];
        } else {
            int j = Pidx[i], k = Qidx[i];
            int sec1 = q[i - j];
            int sec2 = p[i - k];
            int sec = sec1 > sec2 ? sec1 : sec2;
            sum = pow2[pv] + pow2[sec];
        }
        ans[i] = sum % MOD;
    }
 
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i + 1 < n ? ' ' : '\n');
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}