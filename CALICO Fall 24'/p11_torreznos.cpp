/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define fastinput ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define sz(x) ((int)(x).size())

class DSU {
public:
    vector<int> par, sz;
    DSU(int n) {
        par.resize(n);
        sz.assign(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        return par[x] == x ? x : par[x] = find(par[x]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        return true;
    }
    int size(int x) {
        return sz[find(x)];
    }
};


class Matroid {
protected:
    int n;
    set<int> iset, gset, cset;

public:
    Matroid(int _n) : n(_n) {
        for (int i = 0; i < n; ++i) {
            gset.insert(i);
            cset.insert(i);
        }
    }

    virtual bool independent() = 0;

    virtual void insert(int e) {
        iset.insert(e);
        cset.erase(e);
    }

    virtual void erase(int e) {
        iset.erase(e);
        cset.insert(e);
    }

    bool find(int e) {
        return iset.find(e) != iset.end();
    }

    set<int> ground_set() { return gset; }
    set<int> current_set() { return iset; }
    set<int> complement_set() { return cset; }

    virtual vector<vector<int>> compute_all_circuits() {
        vector<vector<int>> answers(n);
        for (auto y : complement_set()) {
            insert(y);
            if (independent()) {
                erase(y);
                continue;
            }
            for (auto x : current_set()) {
                erase(x);
                if (independent()) {
                    answers[y].push_back(x);
                }
                insert(x);
            }
            erase(y);
        }
        return answers;
    }
};

class SpecialBondMatroid : public Matroid {
public:
    int V;
    vector<pair<int, int>> edges;
    int source, sink;
    DSU dsu;

    SpecialBondMatroid(int _V, const vector<pair<int, int>>& _edges, int _source, int _sink)
        : Matroid(sz(_edges)), V(_V), edges(_edges), source(_source), sink(_sink), dsu(_V) {
        for (int i = 0; i < sz(edges); ++i) {
            if (edges[i].first != sink && edges[i].second != sink) {
                dsu.merge(edges[i].first, edges[i].second);
            }
        }
    }

    void insert(int e) override {
        Matroid::insert(e);
        if (edges[e].first != sink && edges[e].second != sink) {
            dsu = DSU(V);
            for (auto x : current_set()) {
                if (x == e) continue;
                auto [u, v] = edges[x];
                if (u != sink && v != sink) dsu.merge(u, v);
            }
        }
    }

    void erase(int e) override {
        if (!find(e)) return;
        Matroid::erase(e);
        auto [u, v] = edges[e];
        if (u != sink && v != sink) {
            dsu.merge(u, v);
        }
    }

    bool independent() override {
        return dsu.size(source) == V - 1;
    }
};

int weighted_matroid_intersection(int n, Matroid& F1, Matroid& F2, const vector<int>& c) {
    vector<bool> iset(n, false);
    vector<int> c1 = c, c2(n, 0);
    int total_weight = 0, max_weight = 0;

    while (true) {
        vector<vector<int>> C1 = F1.compute_all_circuits();
        vector<vector<int>> C2 = F2.compute_all_circuits();
        vector<pair<int, int>> A1, A2;
        vector<int> S, T;

        for (int y = 0; y < n; ++y) {
            if (iset[y]) continue;
            for (auto x : C1[y]) A1.emplace_back(x, y);
            for (auto x : C2[y]) A2.emplace_back(y, x);

            F1.insert(y);
            if (F1.independent()) S.pb(y);
            F1.erase(y);

            F2.insert(y);
            if (F2.independent()) T.pb(y);
            F2.erase(y);
        }

        vector<vector<int>> G(n);
        for (auto [x, y] : A1) if (c1[x] == c1[y]) G[x].pb(y);
        for (auto [y, x] : A2) if (c2[y] == c2[x]) G[y].pb(x);

        vector<int> par(n, -1);
        queue<int> q;
        for (auto y : S) {
            par[y] = -2;
            q.push(y);
        }

        int found = -1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (find(T.begin(), T.end(), u) != T.end()) {
                found = u; break;
            }
            for (int v : G[u]) {
                if (par[v] == -1) {
                    par[v] = u;
                    q.push(v);
                }
            }
        }

        if (found != -1) {
            while (found >= 0) {
                if (iset[found]) {
                    iset[found] = false;
                    F1.erase(found); F2.erase(found);
                    total_weight -= c[found];
                } else {
                    iset[found] = true;
                    F1.insert(found); F2.insert(found);
                    total_weight += c[found];
                }
                found = par[found];
            }
            max_weight = max(max_weight, total_weight);
        } else break;
    }

    return max_weight;
}

int solve(int N, int M, int F, int S, vector<vector<int>> E) {
    vector<pair<int, int>> edges(M);
    vector<int> weights(M);
    for (int i = 0; i < M; ++i) {
        edges[i] = {E[i][0], E[i][1]};
        weights[i] = E[i][2];
    }

    SpecialBondMatroid F1(N, edges, F, S), F2(N, edges, S, F);
    int total = accumulate(all(weights), 0LL);
    int keep = weighted_matroid_intersection(M, F1, F2, weights);
    return total - keep;
}

int32_t main() {
    fastinput;
    int T;
    cin >> T;
    while (T--) {
        int N, M, F, S;
        cin >> N >> M >> F >> S;
        vector<vector<int>> E(M, vector<int>(3));
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < 3; ++j)
                cin >> E[i][j];
        cout << solve(N, M, F, S, E) << '\n';
    }
}