/*
Tomato_Cultivator 
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi  = vector<int>;

#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)

const int MOD = 1e9+7;

template<class T> bool chmin(T& a,const T& b){ if(b<a){a=b; return true;} return false; }

struct MinPairSeg {
    const pii INF = {int(1e9), 0};
    int n = 0, S = 1;
    vector<pii> t;
    MinPairSeg() {}
    MinPairSeg(int _n){ init(_n); }
    void init(int _n){
        n = _n; S = 1; while(S < n) S <<= 1;
        t.assign(2*S, INF);
    }
    static inline pii combine(const pii& a, const pii& b){
        return (a < b ? a : b);
    }
    void clear(){ fill(all(t), INF); }
    void point_min(int pos, pii val){
        int p = pos + S;
        t[p] = combine(t[p], val);
        for(p >>= 1; p; p >>= 1) t[p] = combine(t[p<<1], t[p<<1|1]);
    }
    pii range_min(int l, int r){
        if(l > r) return INF;
        l += S; r += S;
        pii L = INF, R = INF;
        while(l <= r){
            if(l & 1) { L = combine(L, t[l]); ++l; }
            if(!(r & 1)) { R = combine(t[r], R); --r; }
            l >>= 1; r >>= 1;
        }
        return combine(L, R);
    }
};

void solve(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return;

    vector<int> A(n);
    rep(i,n) cin >> A[i];

    vector<int> L(n), R(n);
    vector<vector<int>> waitAt(n);
    rep(i,n){
        L[i] = max(0, i - A[i]);
        R[i] = min(n-1, i + A[i] - 1);
        if(i >= A[i]) waitAt[i - A[i]].push_back(i);
    }

    const pii INF = {int(1e9), 0};
    vector<pii> dp(n, {int(1e9), -1});

    MinPairSeg seg(n);
    seg.clear();

    rep(i,n){
        if(i+1 <= A[i]) dp[i] = {0, -1};
        dp[i] = min(dp[i], seg.range_min(L[i], i-1));
        if(dp[i].fi < int(1e9)) dp[i].fi++;
        seg.point_min(R[i], {dp[i].fi, i});
        for(int j : waitAt[i]){
            dp[j] = seg.range_min(L[j], R[j]);
        }
    }

    pii tail = seg.range_min(n-1, n-1);
    if(tail.fi > n){
        cout << -1 << '\n';
        return;
    }

    int cur = tail.se;
    vector<int> pick;
    while(cur != -1){
        pick.push_back(cur);
        cur = dp[cur].se;
    }

    sort(all(pick), [&](int x, int y){
        if(A[x] != A[y]) return A[x] < A[y];
        return x < y;
    });

    cout << sz(pick) << '\n';
    for(int idx : pick){
        cout << (idx + 1) << ' ';
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    if(!(cin >> T)) return 0;
    while(T--) solve();
    return 0;
}