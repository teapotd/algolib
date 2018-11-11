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
		ret = min(ret, v.cross(p-hull[i]));
	}
	return max(ret+1, 0);
}
