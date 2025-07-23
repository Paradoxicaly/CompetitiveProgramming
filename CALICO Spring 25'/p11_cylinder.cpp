/*
Derrick (Tomato_Cultivator)
*/

#include <bits/stdc++.h>
using namespace std;

using db = long double;
using Point3D = array<db, 3>;
const db EPS = 1e-5;

bool equals_eps(db a, db b) {
    return abs(a - b) < EPS;
}

struct Plane {
    db a, b, c, d;

    Plane(db a_, db b_, db c_, db d_) {
        db norm = sqrt(a_ * a_ + b_ * b_ + c_ * c_);
        a = a_ / norm;
        b = b_ / norm;
        c = c_ / norm;
        d = d_ / norm;
    }

    static Plane from_points(Point3D p1, Point3D p2, Point3D p3) {
        db a = (p2[1] - p1[1]) * (p3[2] - p1[2]) - (p3[1] - p1[1]) * (p2[2] - p1[2]);
        db b = (p3[0] - p1[0]) * (p2[2] - p1[2]) - (p2[0] - p1[0]) * (p3[2] - p1[2]);
        db c = (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0]);
        db d = -a * p1[0] - b * p1[1] - c * p1[2];
        return Plane(a, b, c, d);
    }

    db signed_distance(Point3D p) const {
        return a * p[0] + b * p[1] + c * p[2] + d;
    }
};

Point3D project_point(const Point3D& p, const Plane& plane) {
    db d = plane.signed_distance(p);
    return {p[0] - d * plane.a, p[1] - d * plane.b, p[2] - d * plane.c};
}

vector<Point3D> project_all(const vector<Point3D>& pts, const Plane& plane) {
    vector<Point3D> res;
    for (const auto& p : pts) res.push_back(project_point(p, plane));
    return res;
}

vector<Point3D> center_points(const vector<Point3D>& pts) {
    db cx = 0, cy = 0, cz = 0;
    for (auto& p : pts) {
        cx += p[0]; cy += p[1]; cz += p[2];
    }
    cx /= pts.size(); cy /= pts.size(); cz /= pts.size();

    vector<Point3D> centered;
    for (auto& p : pts) {
        centered.push_back({p[0] - cx, p[1] - cy, p[2] - cz});
    }
    return centered;
}

db rect_area(const vector<array<db, 2>>& points2D) {
    auto angle = [&](const array<db, 2>& p, db cx, db cy) {
        return atan2(p[1] - cy, p[0] - cx);
    };

    db cx = 0, cy = 0;
    for (auto& p : points2D) {
        cx += p[0]; cy += p[1];
    }
    cx /= points2D.size(); cy /= points2D.size();

    auto sorted = points2D;
    sort(sorted.begin(), sorted.end(), [&](auto& a, auto& b) {
        return angle(a, cx, cy) < angle(b, cx, cy);
    });

    db min_x = 1e18, max_x = -1e18, min_y = 1e18, max_y = -1e18;
    for (auto& p : sorted) {
        min_x = min(min_x, p[0]);
        max_x = max(max_x, p[0]);
        min_y = min(min_y, p[1]);
        max_y = max(max_y, p[1]);
    }

    return (max_x - min_x) * (max_y - min_y);
}

db solve(int N, const vector<db>& X, const vector<db>& Y, const vector<db>& Z) {
    vector<Point3D> pts(N);
    for (int i = 0; i < N; ++i) pts[i] = {X[i], Y[i], Z[i]};

    mt19937 rng(1337);
    uniform_int_distribution<int> dist(0, N - 1);

    while (true) {
        int i = dist(rng), j = dist(rng), k = dist(rng);
        if (i == j || j == k || i == k) continue;

        Plane plane = Plane::from_points(pts[i], pts[j], pts[k]);

        vector<db> dists(N);
        db max_d = -1e18, min_d = 1e18;
        for (int i = 0; i < N; ++i) {
            dists[i] = plane.signed_distance(pts[i]);
            max_d = max(max_d, dists[i]);
            min_d = min(min_d, dists[i]);
        }

        if (!equals_eps(max_d, 0) && !equals_eps(min_d, 0)) continue;

        db height = max(abs(max_d), abs(min_d));
        vector<Point3D> remaining;
        for (int i = 0; i < N; ++i) {
            if (!equals_eps(dists[i], 0) && !equals_eps(abs(dists[i]), height)) {
                remaining.push_back(pts[i]);
            }
        }

        if (remaining.size() < 4) continue;

        auto flat = center_points(project_all(remaining, plane));
        vector<array<db, 2>> projected2D;
        for (auto& p : flat) projected2D.push_back({p[0], p[1]});

        db area = rect_area(projected2D);
        if (area > 0) return area * height;
    }
}

int main() {
    int T;
    cin >> T;
    cout << fixed << setprecision(10);
    while (T--) {
        int N;
        cin >> N;
        vector<db> X(N), Y(N), Z(N);
        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> Y[i] >> Z[i];
        }
        cout << solve(N, X, Y, Z) << '\n';
    }
    return 0;
}