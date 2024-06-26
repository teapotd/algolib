#pragma once
#include "../../../src/geo2d/line.h"
#include "common.hpp"

line canonical(line l) {
#if FLOATING_POINT_GEOMETRY
	auto g = l.v.len();
#else
	auto g = gcd(gcd(l.v.x, l.v.y), l.c);
#endif
	return {l.v/g, l.c/g};
}

bool lineEqual(line a, line b) {
	a = canonical(a);
	b = canonical(b);
	return equalWithEps(a.v, b.v) && equalWithEps(a.c, b.c);
}

void deterministic() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
	line def;
	assert(def.v.x == 0 && def.v.y == 0 && def.c == 0);
#pragma GCC diagnostic pop

	assert(lineEqual(through({2*U,4*U}, {14*U,8*U}), {{1,-3},-10*U}));
	assert(lineEqual(through({14*U,8*U}, {2*U,4*U}), {{-1,3},10*U}));
	assert(lineEqual(parallel({8*U,6*U}, {{-1*U,3*U},-123*U}), {{-1,3},10*U}));
	assert(lineEqual(perp({8*U,6*U}, {{3*U,1*U},-123*U}), {{-1,3},10*U}));

	assert(equalWithEps(line{{U,-3*U},-10*U*U}.dist({8*U,6*U}), 0.0));
	assert(equalWithEps(line{{U,-3*U},-10*U*U}.dist({-5*U,5*U}), sqrt(10)*U));
	assert(equalWithEps(line{{U,-3*U},-10*U*U}.dist({3*U,1*U}), sqrt(10)*U));

	assert((line{{U,-3*U},-10*U*U}.side({8*U,6*U}) == 0));
	assert((line{{U,-3*U},-10*U*U}.side({-5*U,5*U}) == -1));
	assert((line{{U,-3*U},-10*U*U}.side({3*U,1*U}) == 1));

#if FLOATING_POINT_GEOMETRY
	vec intersection;
	assert(!(line{{1,-3},-10}.intersect({{1,-3},-10}, intersection)));
	assert(!(line{{1,-3},-10}.intersect({{1,-3},-11}, intersection)));
	assert(!(line{{1,-3},-10}.intersect({{-1,3},-11}, intersection)));
	assert((line{{0.5,1},7.5}.intersect({{1,-3},-10}, intersection)));
	assert(intersection == vec(5,5));
#endif
}

void fuzz() {
#if FLOATING_POINT_GEOMETRY
	rep(i, 0, 3e6) {
		line l(randVecFromDisk(0.5, 1), randCoord(-1, 1));
		vec inter, p = randVecFromSquare(-5, 5);
		assert(perp(p, l).intersect(l, inter));
		assert(inter == l.proj(p));
	}
#endif
}

void benchmark() {
}
