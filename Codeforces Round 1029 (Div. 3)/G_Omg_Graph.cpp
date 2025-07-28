/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()

const int MAXSZ = 1000009;
const int MODULAR = 1000000007;

void incMod(int &x, int v) {
    x += v;
    if (x >= MODULAR) x -= MODULAR;
}

void decMod(int &x, int v) {
    x -= v;
    if (x < 0) x += MODULAR;
}

int binexp(int base, int exp, int m = MODULAR) {
    base %= m;
    if (base == 0) return 0;
    int res = 1;
    while (exp > 0) {
        if (exp & 1) { res = int((ll)res * base % m); --exp; }
        base = int((ll)base * base % m);
        exp >>= 1;
    }
    return res;
}

int R, E;
vector<pii> graf[MAXSZ];
int distArr[2][MAXSZ];
bool seen[MAXSZ];

void runDijkstra(int which, int start) {
    int INFLL = 1000000000;
    for (int i = 1; i <= R; i++) {
        distArr[which][i] = INFLL;
        seen[i] = false;
    }
    distArr[which][start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [curD, u] = pq.top(); pq.pop();
        if (seen[u]) continue;
        seen[u] = true;
        for (auto &pr : graf[u]) {
            int v = pr.fi, w = pr.se;
            int nd = max(curD, w);
            if (nd < distArr[which][v]) {
                distArr[which][v] = nd;
                pq.push({nd, v});
            }
        }
    }
}

bool cmpByWeight(const pii &A, const pii &B) {
    return A.se < B.se;
}

struct Edge { int a, b, w; };
Edge ed[MAXSZ];

void runCase() {
    cin >> R >> E;
    for (int i = 1; i <= R; i++) graf[i].clear();
    for (int i = 1; i <= E; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        graf[u].pb({v,w});
        graf[v].pb({u,w});
        ed[i] = {u,v,w};
    }
    for (int i = 1; i <= R; i++) {
        sort(all(graf[i]), cmpByWeight);
    }
    runDijkstra(0, 1);
    runDijkstra(1, R);
    int answer = INT_MAX;
    for (int i = 1; i <= E; i++) {
        auto &q = ed[i];
        int cand = q.w + max({ distArr[0][q.a], distArr[1][q.b], q.w });
        answer = min(answer, cand);
    }
    cout << answer << "\n";
}

void clearAll() {
    for (int i = 1; i <= R; i++) {
        graf[i].clear();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC;
    if (fopen("input.txt","r")) {
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }
    cin >> TC;
    while (TC--) {
        runCase();
        clearAll();
    }
    return 0;
}