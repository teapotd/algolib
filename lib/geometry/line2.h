#pragma once
#include "../template.h"
#include "vec2.h"

// 2D line structure; UNTESTED

// Base class of versions for ints and doubles
template<class T, class P, class S>
struct bline2 { // norm*point == off
	P norm; // Normal vector [A; B]
	T off;  // Offset (C parameter of equation)

	// Line through 2 points
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
	double distFrom(P a) {
		return fabs(norm.dot(a)-off) / norm.len();
	}
};

// Version for integer coordinates (long long)
struct line2i : bline2<ll, vec2i, line2i> {
	line2i() : bline2{{}, 0} {}
	line2i(vec2i n, ll c) : bline2{n, c} {}

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

	int side(vec2d a) {
		return cmp(norm.dot(a), off);
	}

	vec2d intersect(line2d a) {
		double d = norm.cross(a.norm);
		assert(cmp(d, 0) != 0); // Not parallel
		return (norm*a.off-a.norm*off).perp() / d;
	}
};

using line2 = line2d;
