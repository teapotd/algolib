#pragma once
#include "../template.h"
#include "vector.h"

// Find convex hull of points; time: O(n lg n)
// Points are returned counter-clockwise,
// first point is the bottom-leftmost.
// Depends on vec: -, cross, cmpXY
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ConvexHull.h
vector<vec> convexHull(vector<vec> points) {
	if (sz(points) <= 1) return points;
	sort(all(points), [](vec l, vec r) {
		return l.cmpYX(r) < 0;
	});
	vector<vec> h(sz(points)+1);
	int s = 0, t = 0;
	rep(i, 0, 2) {
		each(p, points) {
			for (; t >= s+2; t--) {
				auto c = (p-h[t-2]).cross(p-h[t-1]);
				if (cmp(c) > 0) break;
			}
			h[t++] = p;
		}
		reverse(all(points));
		s = --t;
	}
	h.resize(t - (t == 2 && !h[0].cmpYX(h[1])));
	return h;
}
