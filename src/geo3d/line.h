#pragma once
#include "../template.h"
#include "vector.h"

// 3D line structure; UNTESTED
//! Source: https://victorlecomte.com/cp-geo.pdf
struct line3 { // p + d*k == point
	vec3 p, d; // Point and direction

	// Distance from point to line.
	// Depends on vec3: dot, len
	double dist(vec3 a) {
		return d.cross(a-p).len() / d.len();
	}

	// Distance between two lines.
	// Depends on vec3: -, dot, cross, len2
	double dist(line3 a) {
		vec3 n = d.cross(a.d);
		sc t = n.len2();
		if (!sgn(t)) return dist(a.p);
		return fabs(n.dot(a.p-p)) / sqrt(t);
	}

#if FLOATING_POINT_GEOMETRY
	// Closest point to another line.
	// Assumes lines are not parallel!
	// Depends on vec3: -, dot, cross, len
	vec3 closest(line3 a) {
		vec3 n2 = a.d.cross(d.cross(a.d));
		return p + d * n2.dot(a.p-p) / d.dot(n2);
	}

	// Orthogonal projection of point on line.
	// Depends on vec3: -, *, dot, len2
	vec3 proj(vec3 a) {
		return p + d * (d.dot(a-p) / d.len2());
	}
#endif
};

// Line through 2 given points.
// Depends on vec: -
line3 through(vec3 a, vec3 b) {
	return {a, b-a};
}
