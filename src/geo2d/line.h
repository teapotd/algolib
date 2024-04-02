#pragma once
#include "../template.h"
#include "vector.h"

// 2D line/halfplane structure; UNIT-TESTED
struct line {
	// For lines: v * point == c
	// For halfplanes: v * point <= c
	// (i.e. normal vector points outside)
	vec v;        // Normal vector
	vec::T c = 0; // Offset
	DBP(v, c);

	// Distance from point to line.
	// Depends on vec: dot, len
	double dist(vec a) {
		return fabs(v.dot(a) - c) / v.len();
	}

	// Returns 0 if point a lies on the line,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	// Depends on vec: dot
	int side(vec a) { return sgn(v.dot(a)-c); }

#if FLOATING_POINT_GEOMETRY
	// Orthogonal projection of point on line.
	// Depends on vec: -, *, dot, len2
	vec proj(vec a) {
		return a - v * ((v.dot(a)-c) / v.len2());
	}

	// Intersect this line with line a, returns
	// true on success (false if parallel).
	// Intersection point is saved to `out`.
	// Depends on vec: -, *, /, cross, perp
	bool intersect(line a, vec& out) {
		auto d = v.cross(a.v);
		if (!sgn(d)) return 0;
		out = (v*a.c - a.v*c).perp() / d;
		return 1;
	}
#endif
};

// Line through 2 points with normal vector
// pointing to the right of ab vector.
// Depends on vec: -, cross, perp
line through(vec a, vec b) {
	return { (a-b).perp(), a.cross(b) };
}

// Parallel line through point.
// Depends on vec: dot
line parallel(vec a, line b) {
	return { b.v, b.v.dot(a) };
}

// Perpendicular line through point.
// Depends on vec: cross, perp
line perp(vec a, line b) {
	return { b.v.perp(), b.v.cross(a) };
}
