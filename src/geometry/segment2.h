#pragma once
#include "../template.h"
#include "vec2.h"

// 2D segment structure; PARTIALLY TESTED

// Base class of versions for ints and doubles
template<class P, class S> struct bseg2 {
	P a, b; // Endpoints

	// Distance from segment to point
	double distTo(P p) const {
		if ((p-a).dot(b-a) < 0) return (p-a).len();
		if ((p-b).dot(a-b) < 0) return (p-b).len();
		return double(abs((p-a).cross(b-a)))
		              / (b-a).len();
	}
};

// Version for integer coordinates (long long)
struct seg2i : bseg2<vec2i, seg2i> {
	seg2i() {}
	seg2i(vec2i c, vec2i d) : bseg2{c, d} {}

	// Check if segment contains point p
	bool contains(vec2i p) {
		return (a-p).dot(b-p) <= 0 &&
		       (a-p).cross(b-p) == 0;
	}

	// Compare distance to p with sqrt(d2)
	// -1 if smaller, 0 if equal, 1 if greater
	int cmpDistTo(vec2i p, ll d2) const {
		if ((p-a).dot(b-a) < 0) {
			ll l = (p-a).len2();
			return (l > d2) - (l < d2);
		}
		if ((p-b).dot(a-b) < 0) {
			ll l = (p-b).len2();
			return (l > d2) - (l < d2);
		}

		ll c = abs((p-a).cross(b-a));
		d2 *= (b-a).len2();
		return (c*c > d2) - (c*c < d2);
	}
};

// Version for double coordinates
// Requires cmp() from template
struct seg2d : bseg2<vec2d, seg2d> {
	seg2d() {}
	seg2d(vec2d c, vec2d d) : bseg2{c, d} {}

	bool contains(vec2d p) {
		return cmp((a-p).dot(b-p), 0) <= 0 &&
		       cmp((a-p).cross(b-p), 0) == 0;
	}
};

using seg2 = seg2d;
