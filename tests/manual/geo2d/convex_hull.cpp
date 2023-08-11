#define FLOATING_POINT_GEOMETRY 0
#include "../../../src/geo2d/convex_hull.h"
#include "../testing.h"

namespace old_algolib {
	vec normPos(vector<vec>& points) {
		auto q = make_pair(points[0].y, points[0].x);
		each(p, points) q = min(q, make_pair(p.y, p.x));
		vec ret{q.y, q.x};
		each(p, points) p = p-ret;
		return ret;
	}

	vector<vec> convexHull(vector<vec> points) {
		if (points.empty()) return {};
		vec pivot = normPos(points);
		sort(all(points), [](vec l, vec r) {
			return (l.cmpAngle(r) ?: l.len2()-r.len2()) < 0;
		});
		vector<vec> hull;

		each(p, points) {
			while (sz(hull) >= 2) {
				vec a = hull.back() - hull[sz(hull)-2];
				vec b = p - hull.back();
				if (a.cross(b) > 0) break;
				hull.pop_back();
			}
			if (hull.empty() || !(hull.back() == p)) {
				hull.pb(p);
			}
		}

		// Translate back, optional
		each(p, hull) p = p+pivot;
		return hull;
	}
};

int naiveMaxDot(const vector<vec>& hull, vec q) {
	pair<ll, int> ret = { INT64_MAX, 0 };
	rep(i, 0, sz(hull)) {
		ret = min(ret, make_pair(-q.dot(hull[i]), i));
	}
	return ret.y;
}

int naiveInsideHull(vector<vec>& hull, vec p) {
	if (hull.empty()) return 0;
	if (sz(hull) == 1) return hull[0] == p;
	int ret = 1;
	rep(i, 0, sz(hull)) {
		auto v = hull[(i+1)%sz(hull)] - hull[i];
		auto t = v.cross(p-hull[i]);
		ret = min(ret, sgn(t));
	}
	return int(max(ret+1, 0));
}

double naiveHullDist(vector<vec>& hull, vec p) {
	if (naiveInsideHull(hull, p) == 2) return -1;
	double ret = 1e30;
	rep(i, 0, sz(hull)) {
		seg s{hull[(i+1)%sz(hull)], hull[i]};
		ret = min(ret, s.distTo(p));
	}
	return ret;
}

void check(const vector<vec>& points) {
	auto hull = convexHull(points);
	auto expected = old_algolib::convexHull(points);

	assert(hull == expected);

	for (int i = 0; i < sz(hull); i++) {
		for (int j = i+1; j < sz(hull); j++) {
			assert(!(hull[i] == hull[j]));
		}
	}

	for (int i = 1; i < sz(hull); i++) {
		assert(hull[0].cmpYX(hull[i]) < 0);
	}

	if (!hull.empty()) rep(i, 0, 100) {
		vec q = { r(-100, 100), r(-100, 100) };
		assert(maxDot(hull, q) == naiveMaxDot(hull, q));
		assert(floatEqual(hullDist(hull, q), naiveHullDist(hull, q)));
	}
}

int main() {
	while (true) {
		int n = r(0, 100);
		int mx = r(0, 100);
		vector<vec> points(n);
		each(p, points) {
			p.x = r(-mx, mx);
			p.y = r(-mx, mx);
		}
		check(points);
	}
	return 0;
}