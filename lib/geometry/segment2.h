#pragma once
#include "../template.h"
#include "vec2.h"

// 2D segment structure; UNTESTED

// Base class of versions for ints and doubles
template<class P, class S> struct bseg2 {
	P a, b; // Endpoints
};

// Version for integer coordinates (long long)
struct seg2i : bseg2<vec2i, seg2i> {
	seg2i() {}
	seg2i(vec2i c, vec2i d) : bseg2{c, d} {}

	bool contains(vec2i p) {
		return (a-p).dot(b-p) <= 0 &&
		       (a-p).cross(b-p) == 0;
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
