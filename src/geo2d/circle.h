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
	// (greater than 2 means infinity).
	// Arc is CCW w.r.t to `this`, CW for `a`.
	// Depends on vec: +, -, *, len2, perp
	int intersect(circle a, pair<vec,vec>& out) {
		vec d = a.p - p;
		auto d2 = d.len2();
		if (!sgn(d2)) return !sgn(r2-a.r2) ? 3 : 0;
		auto pd = (d2 + r2 - a.r2) / 2;
		auto h2 = r2 - pd*pd / d2;
		vec h, t = p + d*(pd/d2);
		int s = sgn(h2)+1;
		if (s > 1) h = d.perp() * sqrt(h2/d2);
		out = {t-h, t+h};
		return s;
	}

	// Intersect with line.
	// Returns number of intersection points
	int intersect(line a, pair<vec, vec>& out) {
		auto d = a.distTo(p), h2 = r2 - d*d;
		vec h, t = a.proj(p);
		int s = sgn(h2)+1;
		if (s > 1)
			h = a.v.perp() * sqrt(h2 / a.v.len2());
		out = {t-h, t+h};
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
