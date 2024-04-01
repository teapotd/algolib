#pragma once
#include "../template.h"
#include "vector.h" // FLOATING_POINT_GEOMETRY
#include "circle.h"

mt19937 rnd(123);

// Minimum circle enclosing a set of points.
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/MinimumEnclosingCircle.h
circle minDisk(vector<vec> p) { // time: O(n)
	circle c;
	shuffle(all(p), rnd);
	rep(i, 0, sz(p)) if (c.side(p[i]) < 0) {
		c = {p[i], 0};
		rep(j, 0, i) if (c.side(p[j]) < 0) {
			c = {(p[i]+p[j])/2,(p[i]-p[j]).len2()/4};
			rep(k, 0, j) if (c.side(p[k]) < 0)
				c = circum(p[i], p[j], p[k]);
		}
	}
	return c;
}
