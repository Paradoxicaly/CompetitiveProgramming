/*
Tomato_Cultivator
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)

const int N = 1e5 + 1010, B = 500;

int n, q, ans;
int p[N], wp[N], tot;
int tl[N], tr[N];
bool rev[N], ed[N];
queue<int> tq[N], vq[N];
vector<int> cur;


int qq(int x) {
    while (!tq[x].empty()) {
        if (!ed[tq[x].front()]) return tq[x].front();
        tq[x].pop();
    }
    return 0;
}

int query(int x) {
    int s = 0;
    for (int i : cur) {
        s += tr[i] - tl[i] + 1;
        if (s >= x) {
            int g = s - x + 1;
            int y;
            if (rev[i]) {
                y = p[tl[i] + g - 1];
            } else {
                y = p[tr[i] - g + 1];
            }
            while (!vq[y].empty()) {
                int tmp = qq(vq[y].front());
                if (tmp) return tmp;
                vq[y].pop();
            }
            return qq(i);
        }
    }
    assert(false); 
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; ++i) p[i] = i;

    cur.pb(++tot);
    tl[tot] = 1, tr[tot] = n;

    for (int i = 1; i <= q; ++i) {
        int f, x, y;
        cin >> f >> x >> y;

        if (f == 3) {
            x = (x + ans - 1) % q + 1;
        } else {
            x = (x + ans - 1) % n + 1;
        }
        y = (y + ans - 1) % n + 1;

        if (f == 1) {
            int s = 0;
            for (int j : cur) {
                int w = tr[j] - tl[j] + 1;
                s += w;
                if (s >= x) {
                    if (s > x) {
                        tot++;
                        tq[tot] = tq[j];
                        int g = s - x;
                        if (rev[tot] = rev[j]) {
                            tl[tot] = tl[j];
                            tr[tot] = (tl[j] += g) - 1;
                        } else {
                            tr[tot] = tr[j];
                            tl[tot] = (tr[j] -= g) + 1;
                        }
                        cur.insert(next(find(all(cur), j)), tot);
                    }
                    tq[j].push(i);
                    break;
                }
                tq[j].push(i);
            }
        }

        if (f == 2) {
            int s = 0, sz = 0;
            for (int j : cur) {
                ++sz;
                int w = tr[j] - tl[j] + 1;
                s += w;
                if (s >= x) {
                    if (s > x) {
                        tot++;
                        tq[tot] = tq[j];
                        int g = s - x;
                        if (rev[tot] = rev[j]) {
                            tl[tot] = tl[j];
                            tr[tot] = (tl[j] += g) - 1;
                        } else {
                            tr[tot] = tr[j];
                            tl[tot] = (tr[j] -= g) + 1;
                        }
                        cur.insert(next(find(all(cur), j)), tot);
                    }
                    reverse(cur.begin(), cur.begin() + sz);
                    for (int j = 0; j < sz; ++j) rev[cur[j]] ^= 1;
                    break;
                }
            }
        }

        if (f == 3) {
            if (x < i) ed[x] = true;
        }

        cout << (ans = query(y)) << '\n';

        if ((int)cur.size() >= B) {
            int cnt = 0;
            for (int j : cur) {
                if (rev[j]) {
                    for (int k = tr[j]; k >= tl[j]; --k) {
                        vq[wp[++cnt] = p[k]].push(j);
                    }
                } else {
                    for (int k = tl[j]; k <= tr[j]; ++k) {
                        vq[wp[++cnt] = p[k]].push(j);
                    }
                }
            }
            for (int j = 1; j <= n; ++j) p[j] = wp[j];
            cur.clear();
            cur.pb(++tot);
            tl[tot] = 1, tr[tot] = n;
        }
    }

    return 0;
}
