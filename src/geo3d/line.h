#pragma once
#include "../template.h"
#include "vector.h"

// 3D line structure; UNTESTED
//! Source: https://victorlecomte.com/cp-geo.pdf
struct line { // p + d*k == point
	vec p, d; // Point and direction

	// Distance from point to line.
	// Depends on vec: dot, len
	double distTo(vec a) {
		return d.cross(a-p).len() / d.len();
	}

	// Distance between two lines.
	// Depends on vec: -, dot, cross, len
	double distTo(line a) {
		vec n = d.cross(a.d);
		auto t = n.len();
		if (!sgn(t)) return distTo(a.p);
		return abs(n.dot(a.p-p)) / t;
	}

#if FLOATING_POINT_GEOMETRY
	// Closest point to another line.
	// Assumes lines are not parallel!
	// Depends on vec: -, dot, cross, len
	vec closest(line a) {
		vec n2 = a.d.cross(d.cross(a.d));
		return p + d * n2.dot(a.p-p) / d.dot(n2);
	}

	// Orthogonal projection of point on line.
	// Depends on vec: -, *, dot, len2
	vec proj(vec a) {
		return p + d * (d.dot(a-p) / d.len2());
	}
#endif
};
