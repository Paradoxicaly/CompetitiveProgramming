/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define f first
#define s second
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MAXN = 100010;
int n, q;
int sum[MAXN * 4], add[MAXN * 4], diff[MAXN * 4];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : abs(a);
}

void push_down(int t, int l, int r) {
    int mid = (l + r) / 2, lc = t * 2, rc = t * 2 + 1;
    add[lc] += add[t];
    add[rc] += add[t];
    sum[lc] += add[t] * (mid - l + 1);
    sum[rc] += add[t] * (r - mid);
    add[t] = 0;
}

void sum_update(int ql, int qr, int v, int t = 1, int l = 1, int r = n) {
    if (l > qr || r < ql) return;
    if (ql <= l && r <= qr) {
        add[t] += v;
        sum[t] += (r - l + 1) * v;
        return;
    }
    push_down(t, l, r);
    int mid = (l + r) / 2;
    sum_update(ql, qr, v, t * 2, l, mid);
    sum_update(ql, qr, v, t * 2 + 1, mid + 1, r);
    sum[t] = sum[t * 2] + sum[t * 2 + 1];
}

void diff_update(int p, int v, int t = 1, int l = 1, int r = n) {
    if (p < l || p > r) return;
    if (l == r) {
        diff[t] += v;
        return;
    }
    int mid = (l + r) / 2;
    diff_update(p, v, t * 2, l, mid);
    diff_update(p, v, t * 2 + 1, mid + 1, r);
    diff[t] = gcd(diff[t * 2], diff[t * 2 + 1]);
}

int sum_query(int ql, int qr, int t = 1, int l = 1, int r = n) {
    if (ql > qr || l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return sum[t];
    push_down(t, l, r);
    int mid = (l + r) / 2;
    return sum_query(ql, qr, t * 2, l, mid) + sum_query(ql, qr, t * 2 + 1, mid + 1, r);
}

int diff_query(int ql, int qr, int t = 1, int l = 1, int r = n) {
    if (ql > qr || l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return diff[t];
    int mid = (l + r) / 2;
    return gcd(diff_query(ql, qr, t * 2, l, mid), diff_query(ql, qr, t * 2 + 1, mid + 1, r));
}

int gcd_query(int l, int r) {
    if (l > r) return 1;
    return gcd(sum_query(l, l), diff_query(l + 1, r));
}

void solve() {
    cin >> n;
    vector<int> arr(n + 1);
    arr[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        sum_update(i, i, arr[i]);
        diff_update(i, arr[i] - arr[i - 1]);
    }

    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "Update" || op == "U") {
            int l, r, x;
            cin >> l >> r >> x;
            sum_update(l, r, x);
            diff_update(l, x);
            diff_update(r + 1, -x);
        } else {
            int pre = 1;
            int val = sum_query(1, 1);
            int ans = 1e18;

            while (pre <= n) {
                int l = pre, r = n + 1;
                while (l + 1 < r) {
                    int mid = (l + r) / 2;
                    if (gcd_query(1, mid) == val) l = mid;
                    else r = mid;
                }
                val = gcd_query(1, l + 1);
                int left = sum_query(1, l), right = sum_query(l + 1, n);
                ans = min(ans, left / gcd_query(1, l) + right / gcd_query(l + 1, n));
                pre = l + 1;
            }

            int suf = n;
            val = sum_query(n, n);
            while (suf > 0) {
                int l = 0, r = suf;
                while (l + 1 < r) {
                    int mid = (l + r) / 2;
                    if (gcd_query(mid, n) == val) r = mid;
                    else l = mid;
                }
                val = gcd_query(r - 1, n);
                int left = sum_query(1, r - 1), right = sum_query(r, n);
                ans = min(ans, right / gcd_query(r, n) + left / gcd_query(1, r - 1));
                suf = r - 1;
            }

            cout << ans << '\n';
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}