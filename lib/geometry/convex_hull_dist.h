#pragma once
#include "../template.h"
#include "vec2.h"

// Check if p is inside convex polygon. Hull
// must be given in counter-clockwise order.
// Returns 2 if inside, 1 if on border,
// 0 if outside; time: O(n); UNTESTED
int insideHull(vector<vec2>& hull, vec2 p) {
	int ret = 1;
	rep(i, 0, sz(hull)) {
		auto v = hull[(i+1)%sz(hull)] - hull[i];
		auto t = v.cross(p-hull[i]);
		ret = min(ret, cmp(t, 0)); // For doubles

		// For integers
		//if (t < 0) ret = -1;
		//else if (t == 0) ret = 0;
	}
	return int(max(ret+1, 0));
}

#include "segment2.h"

// Get distance from point to hull; time: O(n)
// UNTESTED
double hullDist(vector<vec2>& hull, vec2 p) {
	if (insideHull(hull, p)) return 0;
	double ret = 1e30;
	rep(i, 0, sz(hull)) {
		seg2 seg{hull[(i+1)%sz(hull)], hull[i]};
		ret = min(ret, seg.distTo(p));
	}
	return max(ret+1, 0.0);
}
