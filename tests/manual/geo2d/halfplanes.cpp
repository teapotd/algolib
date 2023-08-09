#define FLOATING_POINT_GEOMETRY 1
#include "../../../src/geo2d/halfplanes.h"
#include "../../../src/geo2d/convex_hull.h"
#include "../testing.h"

vector<vec> naiveIntersect(vector<line> in) {
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
	auto hull = convexHull(points);
	return hull;
}

void check(vector<line> lines) {
	auto fast = intersectHalfs(lines);
	auto naive = naiveIntersect(lines);
	// deb(lines);
	// deb(fast);
	// deb(naive);
	assert(fast == naive);
}

void addBounds(vector<line>& lines, double d) {
	lines.pb({{1, 0}, d});
	lines.pb({{0, 1}, d});
	lines.pb({{-1, 0}, d});
	lines.pb({{0, -1}, d});
}

int main() {
	constexpr int mx = 10;
	constexpr int bounds = 1000;

	for (int t = 0;; t++) {
		int n = r(0, 10);
		vector<line> lines(n);
		each(l, lines) {
			do {
				l.v.x = r(-mx, mx);
				l.v.y = r(-mx, mx);
			} while (!sgn(l.v.x) && !sgn(l.v.y));
			l.c = r(t ? 1 : -mx, mx);
		}
		addBounds(lines, bounds);
		check(lines);
		if (t%int(1e5) == 0) deb(t);
	}

	return 0;
}
