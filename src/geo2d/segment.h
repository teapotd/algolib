#pragma once
#include "../template.h"
#include "vector.h"

// 2D segment structure; UNIT-TESTED
struct seg {
	vec a, b; // Endpoints
	DBP(a, b);

	// Check if segment contains point p.
	// Depends on vec: -, dot, cross
	bool contains(vec p) {
		return (a-p).dot(b-p) <= eps &&
		       !sgn((a-p).cross(b-p));
	}

	// Returns 0 if point p lies on the line ab,
	// 1 if to the left of the vector ab,
	// -1 if on the right of the vector ab.
	// Depends on vec: cross
	int side(vec p) {
		return sgn((b-a).cross(p-a));
	}

	// Distance from segment to point.
	// Depends on vec: -, dot, cross, len
	double dist(vec p) const {
		if ((p-a).dot(b-a) <= eps)
			return (p-a).len();
		if ((p-b).dot(a-b) <= eps)
			return (p-b).len();
		return double(abs((p-a).cross(b-a))) /
			(b-a).len();
	}

#if not FLOATING_POINT_GEOMETRY
	// Compare distance to p with sqrt(d2).
	// -1 if smaller, 0 if equal, 1 if greater
	// Depends on vec: -, dot, cross, len2
	int cmpDist(vec p, ll d2) const {
		if ((p-a).dot(b-a) <= 0)
			return sgn((p-a).len2()-d2);
		if ((p-b).dot(a-b) <= 0)
			return sgn((p-b).len2()-d2);
		ll c = (p-a).cross(b-a);
		return sgn(c*c - d2 * (b-a).len2());
	}
#endif
};
