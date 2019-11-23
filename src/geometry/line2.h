#pragma once
#include "../template.h"
#include "vec2.h"

// 2D line/halfplane structure
// PARTIALLY TESTED

// Base class of versions for ints and doubles
template<class T, class P, class S>
struct bline2 {
	// For lines: norm*point == off
	// For halfplanes: norm*point <= off
	// (i.e. normal vector points outside)
	P norm; // Normal vector [A; B]
	T off;  // Offset (C parameter of equation)

	// Line through 2 points; normal vector
	// points to the left of ab vector
	static S through(P a, P b) {
		return { (b-a).perp(), b.cross(a) };
	}

	// Parallel line through point
	static S parallel(P a, S b) {
		return { b.norm, b.norm.dot(a) };
	}

	// Perpendicular line through point
	static S perp(P a, S b) {
		return { b.norm.perp(), b.norm.cross(a) };
	}

	// Distance from point to line
	double distTo(P a) {
		return fabs(norm.dot(a)-off) / norm.len();
	}
};

// Version for integer coordinates (long long)
struct line2i : bline2<ll, vec2i, line2i> {
	line2i() : bline2{{}, 0} {}
	line2i(vec2i n, ll c) : bline2{n, c} {}

	// Returns 0 if point a lies on the line,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	int side(vec2i a) {
		ll d = norm.dot(a);
		return (d > off) - (d < off);
	}
};

// Version for double coordinates
// Requires cmp() from template
struct line2d : bline2<double, vec2d, line2d> {
	line2d() : bline2{{}, 0} {}
	line2d(vec2d n, double c) : bline2{n, c} {}

	// Returns 0 if point a lies on the line,
	// 1 if on side where normal vector points,
	// -1 if on the other side.
	int side(vec2d a) {
		return cmp(norm.dot(a), off);
	}

	// Intersect this line with line a, returns
	// true on success (false if parallel).
	// Intersection point is saved to `out`.
	bool intersect(line2d a, vec2d& out) {
		double d = norm.cross(a.norm);
		if (cmp(d, 0) == 0) return false;
		out = (norm*a.off-a.norm*off).perp() / d;
		return true;
	}
};

using line2 = line2d;
