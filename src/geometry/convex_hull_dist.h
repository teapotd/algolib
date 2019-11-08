#pragma once
#include "../template.h"
#include "vec2.h"

// Check if p is inside convex polygon. Hull
// must be given in counter-clockwise order.
// Returns 2 if inside, 1 if on border,
// 0 if outside; time: O(n)
int insideHull(vector<vec2>& hull, vec2 p) {
	int ret = 1;
	rep(i, 0, sz(hull)) {
		auto v = hull[(i+1)%sz(hull)] - hull[i];
		auto t = v.cross(p-hull[i]);
		ret = min(ret, cmp(t, 0)); // For doubles
		//ret = min(ret, (t>0) - (t<0)); // Ints
	}
	return int(max(ret+1, 0));
}

#include "segment2.h"

// Get distance from point to hull; time: O(n)
double hullDist(vector<vec2>& hull, vec2 p) {
	if (insideHull(hull, p)) return 0;
	double ret = 1e30;
	rep(i, 0, sz(hull)) {
		seg2 seg{hull[(i+1)%sz(hull)], hull[i]};
		ret = min(ret, seg.distTo(p));
	}
	return ret;
}

// Compare distance from point to hull
// with sqrt(d2); time: O(n)
// -1 if smaller, 0 if equal, 1 if greater
int cmpHullDist(vector<vec2>& hull,
                vec2 p, ll d2) {
	if (insideHull(hull,p)) return (d2<0)-(d2>0);
	int ret = 1;
	rep(i, 0, sz(hull)) {
		seg2 seg{hull[(i+1)%sz(hull)], hull[i]};
		ret = min(ret, seg.cmpDistTo(p, d2));
	}
	return ret;
}
