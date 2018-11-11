#pragma once
#include "../template.h"
#include "vec2.h"

// Translate points such that lower-left point
// is (0, 0). Returns old point location; O(n)
vec2 normPos(vector<vec2>& points) {
	auto pivot = points[0].yxPair();
	each(p,points) pivot = min(pivot,p.yxPair());
	vec2 ret{pivot.y, pivot.x};
	each(p, points) p = p-ret;
	return ret;
}

// Find convex hull of points; time: O(n lg n)
// Points are returned counter-clockwise.
vector<vec2> convexHull(vector<vec2> points) {
	vec2 pivot = normPos(points);
	sort(all(points));
	vector<vec2> hull;

	each(p, points) {
		while (sz(hull) >= 2) {
			vec2 prev = hull.back()-hull[sz(hull)-2];
			vec2 cur = p - hull.back();
			if (prev.cross(cur) > 0) break;
			hull.pop_back();
		}
		hull.pb(p);
	}

	// Translate back, optional
	each(p, hull) p = p+pivot;
	return hull;
}
