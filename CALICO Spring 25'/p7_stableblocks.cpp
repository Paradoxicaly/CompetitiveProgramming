/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

void solve() {
    int n;
    cin >> n;
    vector<ll> x0(n), y0(n), x1(n), y1(n);
    rep(i, n) cin >> x0[i] >> y0[i] >> x1[i] >> y1[i];

    unordered_map<ll, vector<tuple<ll,ll,int>>> mapY;
    mapY.reserve(n);

    rep(i, n) mapY[y1[i]].emplace_back(x0[i], x1[i], i);
    for (auto &[_, vec] : mapY)
        sort(all(vec), [](auto &a, auto &b) { return get<0>(a) < get<0>(b); });

    vector<int> par(n, -1);
    rep(i, n) {
        if (y0[i] == 0) continue;
        auto &vec = mapY[y0[i]];
        ll L = x0[i], R = x1[i];
        int lo = 0, hi = vec.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (get<0>(vec[mid]) <= R) lo = mid + 1;
            else hi = mid;
        }
        par[i] = get<2>(vec[lo - 1]);
    }

    vector<vector<int>> ch(n);
    vector<int> roots;
    rep(i, n) {
        if (par[i] >= 0) ch[par[i]].pb(i);
        else roots.pb(i);
    }

    vector<ld> mass(n), cx(n);
    rep(i, n) {
        mass[i] = ld(x1[i] - x0[i]) * (y1[i] - y0[i]);
        cx[i] = (ld(x0[i]) + x1[i]) * 0.5;
    }

    vector<ld> subMass(n), subCx(n);
    bool ok = true;
    vector<pair<int, int>> stk;
    for (int r : roots) stk.emplace_back(r, 0);

    while (ok && !stk.empty()) {
        auto [u, st] = stk.back(); stk.pop_back();
        if (st == 0) {
            stk.emplace_back(u, 1);
            for (int v : ch[u]) stk.emplace_back(v, 0);
        } else {
            ld m = mass[u], xc = mass[u] * cx[u];
            for (int v : ch[u]) {
                m += subMass[v];
                xc += subMass[v] * subCx[v];
            }
            subMass[u] = m;
            subCx[u] = xc / m;
            int p = par[u];
            if (p >= 0 && (subCx[u] < x0[p] || subCx[u] > x1[p])) {
                ok = false;
            }
        }
    }

    cout << (ok ? "Stable\n" : "Unstable\n");
}

int main() {
    cincout();
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}