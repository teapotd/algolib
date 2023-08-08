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
			if (hull.empty() || hull.back().cmpYX(p)) {
				hull.pb(p);
			}
		}

		// Translate back, optional
		each(p, hull) p = p+pivot;
		return hull;
	}
};

void check(const vector<vec>& points) {
	auto got = convexHull(points);
	auto expected = old_algolib::convexHull(points);

	assert(sz(got) == sz(expected));
	rep(i, 0, sz(got)) {
		assert(!got[i].cmpYX(expected[i]));
	}

	for (int i = 0; i < sz(got); i++) {
		for (int j = i+1; j < sz(got); j++) {
			assert(got[i].cmpYX(got[j]) != 0);
		}
	}

	for (int i = 1; i < sz(got); i++) {
		assert(got[0].cmpYX(got[i]) < 0);
	}
}

int main() {
	while (true) {
		int n = r(0, 50);
		int mx = r(0, 20);
		vector<vec> points(n);
		each(p, points) {
			p.x = r(-mx, mx);
			p.y = r(-mx, mx);
		}
		check(points);
	}
	return 0;
}
