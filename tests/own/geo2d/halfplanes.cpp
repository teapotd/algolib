#define FLOATING_POINT_GEOMETRY 1
#include "../../../src/geo2d/halfplanes.h"
#include "../../../src/geo2d/convex_hull.h"
#include "common.hpp"

vector<vec> naiveHalfplaneIntersection(vector<line> in) {
	vector<vec> points;
	rep(i, 0, sz(in)) rep(j, i+1, sz(in)) {
		vec p;
		if (in[i].intersect(in[j], p)) {
			bool ok = 1;
			each(l, in) {
				if (l.side(p) > 0) {
					ok = 0;
					break;
				}
			}
			if (ok) {
				points.pb(p);
			}
		}
	}
	return convexHull(points);
}

void addBoundingBox(vector<line>& lines, double d) {
	lines.pb({{1, 0}, d});
	lines.pb({{0, 1}, d});
	lines.pb({{-1, 0}, d});
	lines.pb({{0, -1}, d});
}

void check(const vector<line>& lines) {
	auto fast = intersectHalfs(lines);
	auto naive = naiveHalfplaneIntersection(lines);
	assert(fast == naive);
}

vector<line> randLines(int n, int minA, int maxA, int minC, int maxC) {
	vector<line> lines(n);
	for (auto& l : lines) {
		do {
			l.v.x = randInt(minA, maxA);
			l.v.y = randInt(minA, maxA);
		} while (l.v == vec(0, 0));
		l.c = randInt(minC, maxC);
	}
	addBoundingBox(lines, 1e4);
	return lines;
}

void deterministic() {
	check({ {{1,2},3}, {{-1,-2},-3}, {{3,-5},5}, {{-3,5},5} });
	check({ {{1,2},3}, {{3,-7},5}, {{-4,5},-8} });
}

void fuzz() {
	rep(i, 0, 50'000) {
		int n = randInt(1, 50);
		int mx = randInt(1, 100);
		auto lines = randLines(n, -mx, mx, i%10 ? 1 : -mx, mx);
		check(lines);
	}
}

void benchmark() {
	auto lines = randLines(1e6, -1e5, 1e5, 1e4, 1e4);

	measure("intersectHalfs N=1e6", 5, [&] {
		auto hull = intersectHalfs(lines);
		consume(&hull);
	});
}
