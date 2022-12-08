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
		return cmp((a-p).dot(b-p), 0) <= 0 &&
		       cmp((a-p).cross(b-p), 0) == 0;
	}

	// Distance from segment to point.
	// Depends on vec: -, dot, cross, len
	double distTo(vec p) const {
		if ((p-a).dot(b-a) < 0) return (p-a).len();
		if ((p-b).dot(a-b) < 0) return (p-b).len();
		return double(
			abs((p-a).cross(b-a))) / (b-a).len();
	}

#if not FLOATING_POINT_GEOMETRY
	// Compare distance to p with sqrt(d2).
	// -1 if smaller, 0 if equal, 1 if greater
	// Depends on vec: -, dot, cross, len2
	int cmpDistTo(vec p, ll d2) const {
		if ((p-a).dot(b-a) < 0)
			return cmp((p-a).len2(), d2);
		if ((p-b).dot(a-b) < 0)
			return cmp((p-b).len2(), d2);
		ll c = (p-a).cross(b-a);
		return cmp(c*c, d2 * (b-a).len2());
	}
#endif
};
