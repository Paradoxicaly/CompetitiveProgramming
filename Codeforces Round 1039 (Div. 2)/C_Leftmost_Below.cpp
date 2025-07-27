/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i,n) for (int i = 0; i < (n); ++i)

template<class... T>
void input(T&... a){ (cin >> ... >> a); }

template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a; (cout << ... << (cout << ' ', b)); cout << '\n';
}

inline bool is_bad5(const vector<int>& q) {
    int m = q.size();
    if (m < 5) return false;
    int a = q[m-5], b = q[m-4], c = q[m-3], d = q[m-2], e = q[m-1];
    return (a<b && b<c && c<d && d<e) || (a>b && b>c && c>d && d>e);
}

void solve() {
    int n; 
    input(n);
    vi p(n);
    rep(i,n) input(p[i]);

    string answer;
    int K = min(7, n);

    for (int mask = 0; mask < (1<<K); ++mask) {
        int l = 0, r = n-1;
        vector<int> q;
        q.reserve(n);
        string s;
        bool ok = true;

        rep(i, K) {
            int x;
            if (mask & (1<<i)) {
                x = p[l++];
                s.push_back('L');
            } else {
                x = p[r--];
                s.push_back('R');
            }
            q.push_back(x);
            if (is_bad5(q)) { ok = false; break; }
        }
        if (!ok) continue;

        while (l <= r) {
            int m = q.size();
            int xL = p[l], xR = p[r];
            bool safeL = true, safeR = true;
            if (m >= 4) {
                int a = q[m-4], b = q[m-3], c = q[m-2], d = q[m-1];
                if ((a<b && b<c && c<d && d<xL) ||
                    (a>b && b>c && c>d && d>xL)) safeL = false;
                if ((a<b && b<c && c<d && d<xR) ||
                    (a>b && b>c && c>d && d>xR)) safeR = false;
            }
            if (!safeL && !safeR) { ok = false; break; }
            if (safeL) {
                q.push_back(xL);
                s.push_back('L');
                ++l;
            } else {
                q.push_back(xR);
                s.push_back('R');
                --r;
            }
        }

        if (ok && (int)q.size() == n) {
            answer = s;
            break;
        }
    }

    if (answer.empty()) answer = string(n, 'L');
    print(answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    input(T);
    while (T--) solve();
    return 0;
}