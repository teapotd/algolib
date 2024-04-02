#pragma once
#include "../template.h"
#include "vector.h"
#include "line.h" // For line intersections.

// 2D circle structure; UNIT-TESTED
//! Source: https://victorlecomte.com/cp-geo.pdf
struct circle {
	vec p;         // Center
	vec::T r2 = 0; // Squared radius
	DBP(p, r2);

	// Returns -1 if point q lies outside circle,
	// 0 if on the edge, 1 if strictly inside.
	// Depends on vec: -, len2
	int side(vec a) {
		return sgn(r2 - (p-a).len2());
	}

#if FLOATING_POINT_GEOMETRY
	// Intersect with another circle.
	// Returns number of intersection points
	// (3 means circles are identical).
	// Arc is CCW w.r.t to `this`, CW for `a`.
	// Depends on vec: +, -, *, len2, perp
	int intersect(circle a, pair<vec,vec>& out) {
		vec d = a.p - p;
		auto d2 = d.len2();
		if (!sgn(d2)) return sgn(r2-a.r2) ? 0 : 3;
		auto pd = (d2 + r2 - a.r2) / 2;
		auto h2 = r2 - pd*pd / d2;
		vec h, t = p + d*(pd/d2);
		int s = sgn(h2)+1;
		if (s > 1) h = d.perp() * sqrt(h2/d2);
		out = {t-h, t+h};
		return s;
	}

	// Intersect with line.
	// Returns number of intersection points.
	// Points are in order given by a.v.perp().
	int intersect(line a, pair<vec, vec>& out) {
		auto d = a.distTo(p), h2 = r2 - d*d;
		vec h, t = a.proj(p);
		int s = sgn(h2)+1;
		if (s > 1)
			h = a.v.perp() * sqrt(h2 / a.v.len2());
		out = {t-h, t+h};
		return s;
	}

	// Find normal vectors of tangents.
	// Returns number of tangent points
	// (3 means circle is degenerated to `a`).
	// Covered arc is CCW between vectors.
	int tangents(vec a, pair<vec, vec>& out) {
		vec d = a - p;
		auto d2 = d.len2(), h2 = d2 - r2;
		if (!sgn(d2)) return sgn(h2) ? 0 : 3;
		vec h, t = d * sqrt(r2);
		int s = sgn(h2)+1;
		if (s > 1) h = d.perp() * sqrt(h2);
		out = {(t-h)/d2, (t+h)/d2};
		return s;
	}

	// Find normal vectors of tangents.
	// Returns number of tangent points
	// (3 means circles are identical).
	// Arc for `this` is CCW between vectors.
	// For `a`, it is CW for outer, CCW for inner
	int tangents(circle a, bool inner,
	             pair<vec, vec>& out) {
		vec d = a.p - p;
		auto d2 = d.len2();
		auto dr = sqrt(r2)+sqrt(a.r2)*(inner*2-1);
		auto h2 = d2 - dr*dr;
		if (!sgn(d2)) return sgn(h2) ? 0 : 3;
		vec h, t = d * dr;
		int s = sgn(h2)+1;
		if (s > 1) h = d.perp() * sqrt(h2);
		out = {(t-h)/d2, (t+h)/d2};
		return s;
	}
#endif
};

#if FLOATING_POINT_GEOMETRY
// Circumcircle. Points must be non-aligned.
// Depends on vec: +,-,*,/, cross, len2, perp
circle circum(vec a, vec b, vec c) {
	b = b-a; c = c-a;
	auto s = b.cross(c);
	assert(sgn(s));
	vec p = a+(b*c.len2()-c*b.len2()).perp()/s/2;
	return { p, (p-a).len2() };
}
#endif
