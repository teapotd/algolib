#pragma once
#include "../template.h"
#include "vec2.h"

// 2D line/halfplane structure
// PARTIALLY TESTED

// Base class of versions for ints and doubles
template<class T, class P, class S>
struct bline2 {
	// For lines: v * point == c
	// For halfplanes: v * point <= c
	// (i.e. normal vector points outside)
	P v; // Normal vector [A; B]
	T c; // Offset (C parameter of equation)
	DBP(v, c);

	// Line through 2 points; normal vector
	// points to the right of ab vector
	static S through(P a, P b) {
		return { (a-b).perp(), a.cross(b) };
	}

	// Parallel line through point
	static S parallel(P a, S b) {
		return { b.v, b.v.dot(a) };
	}

	// Perpendicular line through point
	static S perp(P a, S b) {
		return { b.v.perp(), b.v.cross(a) };
	}

	// Distance from point to line
	double distTo(P a) {
		return fabs(v.dot(a)-c) / v.len();
	}
};

// Version for integer coordinates (long long)
struct line2i : bline2<ll, vec2i, line2i> {
	line2i() : bline2{{}, 0} {}
	line2i(vec2i a, ll b) : bline2{a, b} {}

	// Returns 0 if point a lies on the line,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	int side(vec2i a) {
		ll d = v.dot(a);
		return (d > c) - (d < c);
	}
};

// Version for double coordinates
// Requires cmp() from template
struct line2d : bline2<double, vec2d, line2d> {
	line2d() : bline2{{}, 0} {}
	line2d(vec2d a, double b) : bline2{a, b} {}

	// Returns 0 if point a lies on the line,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	int side(vec2d a) { return cmp(v.dot(a),c); }

	// Intersect this line with line a, returns
	// true on success (false if parallel).
	// Intersection point is saved to `out`.
	bool intersect(line2d a, vec2d& out) {
		double d = v.cross(a.v);
		if (!cmp(d, 0)) return 0;
		out = (v*a.c - a.v*c).perp() / d;
		return 1;
	}
};

using line2 = line2d;
