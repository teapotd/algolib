#pragma once
#include "../../../src/geo2d/convex_hull.h"
#include "../testing.hpp"

#if FLOATING_POINT_GEOMETRY
constexpr double U = 0.1;
#else
constexpr int U = 1;
#endif

vec randFromDisk(double R) {
	double r = sqrt(randDouble()) * R;
	double a = randDouble(0, M_PI*2);
	double x = r * cos(a), y = r * sin(a);
	return {vec::T(x), vec::T(y)};
}

int naiveInsideHull(const vector<vec>& hull, vec p) {
	if (hull.empty()) return 0;
	if (sz(hull) == 1) return hull[0] == p;
	if (sz(hull) == 2) {
		auto a = hull[0], b = hull[1];
		return sgn((a-p).dot(b-p)) <= 0 && !sgn((a-p).cross(b-p));
	}
	int ret = 1;
	rep(i, 0, sz(hull)) {
		auto v = hull[(i+1)%sz(hull)] - hull[i];
		auto t = v.cross(p-hull[i]);
		ret = min(ret, sgn(t));
	}
	return int(max(ret+1, 0));
}

vector<vec> naiveConvexHull(vector<vec> points) {
	sort(all(points), [](vec l, vec r) {
		return make_pair(l.y, l.x) < make_pair(r.y, r.x);
	});

	points.erase(unique(all(points)), points.end());

	erase_if(points, [&](vec p) {
		rep(a, 0, sz(points)) if (points[a] != p) {
			rep(b, a+1, sz(points)) if (points[b] != p) {
				if (naiveInsideHull({points[a], points[b]}, p)) {
					return true;
				}
			}
		}
		return false;
	});

	erase_if(points, [&](vec p) {
		rep(a, 0, sz(points)) if (points[a] != p) {
			rep(b, a+1, sz(points)) if (points[b] != p) {
				rep(c, b+1, sz(points)) if (points[c] != p) {
					if (naiveInsideHull({points[a], points[b], points[c]}, p)) {
						return true;
					}
					if (naiveInsideHull({points[c], points[b], points[a]}, p)) {
						return true;
					}
				}
			}
		}
		return false;
	});

	if (!points.empty()) {
		sort(1+all(points), [&](vec l, vec r) {
			return (l-points[0]).cmpAngle(r-points[0]) < 0;
		});
	}

	return points;
}

int naiveMaxDot(const vector<vec>& hull, vec q) {
	pair<vec::T, int> ret = { INT64_MAX, 0 };
	rep(i, 0, sz(hull)) {
		ret = min(ret, make_pair(-q.dot(hull[i]), i));
	}
	return ret.y;
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
	auto expected = naiveConvexHull(points);

	assert(hull == expected);

	for (int i = 0; i < sz(hull); i++) {
		for (int j = i+1; j < sz(hull); j++) {
			assert(!(hull[i] == hull[j]));
		}
	}

	for (int i = 1; i < sz(hull); i++) {
		assert(hull[0].cmpYX(hull[i]) < 0);
	}

	for (int i = 2; i < sz(hull); i++) {
		vec a = hull[i-1] - hull[i-2];
		vec b = hull[i] - hull[i-1];
		assert(a.cmpAngle(b) < 0);
	}

	if (!hull.empty()) rep(i, 0, 800) {
		vec q = { randRange(-100*U, 100*U), randRange(-100*U, 100*U) };
		assert(maxDot(hull, q) == naiveMaxDot(hull, q));
		assert(equalWithEps(hullDist(hull, q), naiveHullDist(hull, q)));
	}
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 1000) {
		int n = randInt(0, 30);
		auto mx = randRange(0*U, 100*U);
		vector<vec> points(n);
		each(p, points) {
			p.x = randRange(-mx, mx);
			p.y = randRange(-mx, mx);
		}
		check(points);
	}
}

void benchmark() {
	constexpr int N = 1e6;
	vector<vec> points(N);

	for (auto& p : points) {
		p = randFromDisk(1e9);
	}

	measure("convexHull N=1e6", 5, [&] {
		auto hull = convexHull(points);
		consume(&hull);
	});
}
