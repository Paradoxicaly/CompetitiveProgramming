/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rng(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()

void cincout() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
}

int main() {
    cincout();

    ostringstream buf;
    buf << cin.rdbuf();
    string raw = buf.str(), cleaned;
    cleaned.reserve(raw.size());

    rep(i, raw.size()) {
        char c = raw[i];
        if (c == '-' && i > 0 && i + 1 < raw.size()
            && (isdigit(raw[i - 1]) || raw[i - 1] == '.')
            && (isdigit(raw[i + 1]) || raw[i + 1] == '.')) {
            cleaned.pb(' ');
        }
        cleaned.pb(c);
    }

    istringstream in(cleaned);
    int T;
    in >> T;

    while (T--) {
        int N;
        in >> N;
        double minX = 1e18, maxX = -1e18, minY = 1e18, maxY = -1e18;
        rep(i, N) {
            double x, y;
            in >> x >> y;
            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);
        }
        double width = maxX - minX;
        double height = maxY - minY;
        double area = width * height;
        cout << area << '\n';
    }

    return 0;
}