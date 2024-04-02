#pragma once
#include "../../../src/geo2d/convex_hull.h"
#include "common.hpp"

int naiveInsideHull(const vector<vec>& hull, vec p) {
	if (hull.empty()) {
		return 0;
	}

	if (sz(hull) == 1) {
		return hull[0] == p;
	}

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

int naiveMaxDot(const vector<vec>& hull, vec q) {
	pair<vec::T, int> ret = { numeric_limits<vec::T>::max(), 0 };
	rep(i, 0, sz(hull)) {
		ret = min(ret, make_pair(-q.dot(hull[i]), i));
	}
	return ret.y;
}

double naiveHullDist(const vector<vec>& hull, vec p) {
	if (naiveInsideHull(hull, p) == 2) return -1;
	double ret = 1e30;
	rep(i, 0, sz(hull)) {
		seg s{hull[(i+1)%sz(hull)], hull[i]};
		ret = min(ret, s.dist(p));
	}
	return ret;
}

vector<vec> verifiedConvexHull(const vector<vec>& points) {
	auto hull = convexHull(points);

	// Vertices are pairwise different.
	for (int i = 0; i < sz(hull); i++) {
		for (int j = i+1; j < sz(hull); j++) {
			assert(!(hull[i] == hull[j]));
		}
	}

	// First vertex is the lowest-leftmost.
	for (int i = 1; i < sz(hull); i++) {
		assert(hull[0].cmpYX(hull[i]) < 0);
	}

	// CCW ordering of vertices around the lowest-leftmost.
	for (int i = 2; i < sz(hull); i++) {
		vec a = hull[i-1] - hull[0];
		vec b = hull[i] - hull[0];
		assert(a.cmpAngle(b) < 0);
	}

	// CCW ordering of consecutive edges.
	for (int i = 2; i < sz(hull); i++) {
		vec a = hull[i-1] - hull[i-2];
		vec b = hull[i] - hull[i-1];
		assert(a.cmpAngle(b) < 0);
	}

	// Hull vertices are contained in the input set.
	for (vec p : hull) {
		assert(count(all(points), p) > 0);
	}

	// Input points are inside hull.
	for (vec p : points) {
		assert(naiveInsideHull(hull, p));
	}

	return hull;
}

void deterministic() {
	for (int n = 0; n <= 8; n++) {
		for (int mask = 0; mask < (1<<(n*2)); mask++) {
			vector<vec> points;
			for (int i = 0; i < n; i++) {
				int x = (mask >> (i*2)) & 1;
				int y = (mask >> (i*2+1)) & 1;
				points.pb({x*U, y*U});
			}
			verifiedConvexHull(points);
		}
	}
}

void fuzz() {
	rep(i, 0, 30'000) {
		int n = randInt(1, 200);
		auto mx = randCoord(1*U, 100*U);
		auto points = (i%2 ? randVecsFromSquare(n, -mx, mx) : randVecsFromDisk(n, 0, double(mx)));

		vec offset = randVecFromSquare(-mx*2, mx*2);
		for (auto& p : points) {
			p = p+offset;
		}

		auto hull = verifiedConvexHull(points);
		assert(!hull.empty());

		rep(j, 0, 10) {
			vec q = randVecFromSquare(-100*U, 100*U);
			assert(maxDot(hull, q) == naiveMaxDot(hull, q));
			assert(equalWithEps(hullDist(hull, q), naiveHullDist(hull, q)));
		}
	}
}

void benchmark() {
	auto points = randVecsFromDisk(1e6, 9e8, 1e9);

	measure("convexHull N=1e6", 5, [&] {
		auto hull = convexHull(points);
		consume(&hull);
	});
}
