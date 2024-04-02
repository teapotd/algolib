#pragma once
#include "../template.h"
#include "vector.h"
#include "line.h" // For intersections

// 3D plane/halfspace structure; UNTESTED
//! Source: https://victorlecomte.com/cp-geo.pdf
struct plane {
	// For planes: v * point == c
	// For halfspaces: v * point <= c
	// (i.e. normal vector points outside)
	vec v;        // Normal vector
	vec::T c = 0; // Offset

	// Distance from point to plane.
	// Depends on vec: dot, len
	double distTo(vec a) {
		return fabs(v.dot(a) - c) / v.len();
	}

	// Returns 0 if point a lies on the plane,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	// Depends on vec: dot
	int side(vec a) { return sgn(v.dot(a)-c); }

#if FLOATING_POINT_GEOMETRY
	// Orthogonal projection of point on plane.
	// Depends on vec: -, *, dot, len2
	vec proj(vec a) {
		return a - v * ((v.dot(a)-c) / v.len2());
	}

	// Intersect this plane with line a, returns
	// true on success (false if parallel).
	// Intersection point is saved to `out`.
	// Depends on vec: -, *, dot
	bool intersect(line a, vec& out) {
		auto t = v.dot(a.d);
		if (!sgn(t)) return 0;
		out = a.p - a.d * ((v.dot(a.p)-c) / t);
		return 1;
	}

	// Intersect this plane with plane a, returns
	// true on success (false if parallel).
	// Depends on vec: -, *, /, dot, cross, len2
	bool intersect(plane a, line& out) {
		auto t = (out.d = v.cross(a.v)).len2();
		if (!sgn(t)) return 0;
		out.p = (a.v*c - v*a.c).cross(out.d) / t;
		return 1;
	}
#endif
};

// Plane given by a point and normal vector.
// Depends on vec: dot
plane through(vec v, vec p) {
	return { v, v.dot(p) };
}

// Plane through 3 points with normal vector
// pointing upward when viewed CCW.
// Depends on vec: -, dot, cross
plane through(vec a, vec b, vec c) {
	return through((b-a).cross(c-a), a);
}
