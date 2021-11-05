#pragma once
#include "../template.h"
#include "vec2.h"

// Translate points such that lower-left point
// is (0, 0). Returns old point location; O(n)
vec2 normPos(vector<vec2>& points) {
	auto q = points[0].yx();
	each(p, points) q = min(q, p.yx());
	vec2 ret{q.y, q.x};
	each(p, points) p = p-ret;
	return ret;
}

// Find convex hull of points; time: O(n lg n)
// Points are returned counter-clockwise,
// first point is the lowest-left.
vector<vec2> convexHull(vector<vec2> points) {
	vec2 pivot = normPos(points);
	sort(all(points));
	vector<vec2> hull;

	each(p, points) {
		while (sz(hull) >= 2) {
			vec2 a = hull.back() - hull[sz(hull)-2];
			vec2 b = p - hull.back();
			if (a.cross(b) > 0) break;
			hull.pop_back();
		}
		hull.pb(p);
	}

	// Translate back, optional
	each(p, hull) p = p+pivot;
	return hull;
}

// Find point p that minimizes dot product p*q.
// Returns point index in hull; time: O(lg n)
// If multiple points have same dot product
// one with smallest index is returned.
// Points are expected to be in the same order
// as output from convexHull function.
int minDot(const vector<vec2>& hull, vec2 q) {
	auto C = [](vec2 a, vec2 b) {
		return mp(a.dot(b), a.cross(b));
	};
	auto search = [&](int b, int e, vec2 p) {
		int f = b, g = e;
		while (b+1 < e) {
			int m = (b+e) / 2;
			(C(p, hull[m-1]) > C(p, hull[m])
				? b : e) = m;
		}
		rep(i, 0, min(g-f, 2)) {
			if (C(p, hull[f+i]) < C(p, hull[b]))
				b = f+i;
			if (C(p, hull[g-i-1]) < C(p, hull[b]))
				b = g-i-1;
		}
		return b;
	};
	int m = search(0, sz(hull), {0, -1});
	int i = search(0, m, q);
	int j = search(m, sz(hull), q);
	return C(q, hull[i]) > C(q, hull[j])
		? j : i;
}
