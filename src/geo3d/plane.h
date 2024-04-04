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

	// Distance from point to plane.
	// Depends on vec3: dot, len
	double dist(vec3 a) {
		return fabs(v.dot(a) - c) / v.len();
	}

	// Returns 0 if point a lies on the plane,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	// Depends on vec3: dot
	int side(vec3 a) { return sgn(v.dot(a)-c); }

#if FLOATING_POINT_GEOMETRY
	// Orthogonal projection of point on plane.
	// Depends on vec3: -, *, dot, len2
	vec3 proj(vec3 a) {
		return a - v * ((v.dot(a)-c) / v.len2());
	}

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

// Plane given by a point and normal vector.
// Depends on vec3: dot
plane through(vec3 v, vec3 p) {
	return { v, v.dot(p) };
}

// Plane through 3 points with normal vector
// pointing upward when viewed CCW.
// Depends on vec3: -, dot, cross
plane through(vec3 a, vec3 b, vec3 c) {
	return through((b-a).cross(c-a), a);
}
