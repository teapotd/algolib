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
	vec3 v;    // Normal vector
	sc c = 0; // Offset

	// dist, side, proj exactly the same as in 2D

#if FLOATING_POINT_GEOMETRY
	// Intersect this plane with line a, returns
	// true on success (false if parallel).
	// Intersection point is saved to `out`.
	// Depends on vec3: -, *, dot
	bool intersect(line3 a, vec3& out) {
		sc t = v.dot(a.d);
		if (!sgn(t)) return 0;
		out = a.p - a.d * ((v.dot(a.p)-c) / t);
		return 1;
	}

	// Intersect this plane with plane a, returns
	// true on success (false if parallel).
	// Depends on vec3: -, *, /, dot, cross, len2
	bool intersect(plane a, line3& out) {
		sc t = (out.d = v.cross(a.v)).len2();
		if (!sgn(t)) return 0;
		out.p = (a.v*c - v*a.c).cross(out.d) / t;
		return 1;
	}
#endif
};

// Plane through 3 points with normal vector
// pointing upward when viewed CCW.
// Depends on vec3: -, dot, cross
plane span(vec3 a, vec3 b, vec3 c) {
	vec3 v = (b-a).cross(c-a);
	return {v, v.dot(a)};
}
