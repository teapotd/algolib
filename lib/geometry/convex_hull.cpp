#pragma once
#include "../template.h"
#include "vec2.h"

// Find convex hull of points; time: O(n lg n)
// Points are returned counter-clockwise.
vector<vec2> convexHull(vector<vec2> points) {
	auto pivot = mp(points[0].y, points[0].x);
	each(p,points) pivot=min(pivot, mp(p.y,p.x));
	each(p,points) p = p-vec2(pivot.y, pivot.x);

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
	return hull;
}
