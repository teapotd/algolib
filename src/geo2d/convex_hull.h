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
	h.resize(t - (t == 2 && h[0] == h[1]));
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

#include "segment.h"

// Get distance from point to a hull; O(lg n)
// Returns -1 if point is strictly inside.
// Points are expected to be in the same order
// as output from convexHull function.
// Depends on: maxDot
// Depends on vec: -, dot, cross, len, perp,
//                 upper, cmpAngle
// Depends on seg: side, distTo
double hullDist(const vector<vec>& h, vec q) {
	if (sz(h) == 1) return (q-h[0]).len();
	int b = (h[0]-q).upper() ? maxDot(h,{0,1}):0;
	int n = sz(h), e = b+n;
	vec p = h[b];
	while (b+1 < e) {
		int m = (b+e) / 2;
		vec s = h[m%n], t = h[++m%n];
		auto x = (sgn((s-t).cross(q-s)) < 0 ?
			(q-p).cross(s-p) : (s-t).dot(q-s));
		(sgn(x) < !(m%n) ? b : e) = m-1;
	}
	seg s{h[b%n], h[e%n]}, t{h[e%n], h[++e%n]};
	return s.side(q) + t.side(q) < 2 ?
		s.distTo(q) : -1;
}
