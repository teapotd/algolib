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
				if (sgn(c) > 0) break;
			}
			h[t++] = p;
		}
		reverse(all(points));
		s = --t;
	}
	h.resize(t - (t == 2 && !h[0].cmpYX(h[1])));
	return h;
}

// Find point p that maximizes dot product p*q.
// Returns point index in hull; time: O(lg n)
// If multiple points have same dot product
// one with smallest index is returned.
// Points are expected to be in the same order
// as output from convexHull function.
// Depends on vec: -,cross,perp,upper,cmpAngle
int maxDot(const vector<vec>& h, vec q) {
	int b = 0, e = sz(h);
	while (b+1 < e) {
		int m = (b+e) / 2;
		vec s = h[m] - h[m-1];
		(q.perp().cmpAngle(s) > 0 ? b : e) = m;
	}
	return sgn(q.dot(h[b]-h[0])) > 0 ? b : 0;
}
