#pragma once
#include "../../../src/geo2d/circle.h"
#include "common.hpp"

#if FLOATING_POINT_GEOMETRY
vec between(vec p, vec a, vec b) {
	double x = (a-p).angle(), y = (b-p).angle();
	if (x > y) y += M_PI*2;
	return p + (a-p).rotate((y-x)/2);
}

void circleCircle(circle a, circle b, int expected) {
	pair<vec, vec> out;
	assert(a.intersect(b, out) == expected);

	if (expected == 1) {
		assert(out.x == out.y);
		assert(a.side(out.x) == 0 && b.side(out.x) == 0);
	} else if (expected == 2) {
		assert(out.x != out.y);
		assert(a.side(out.x) == 0 && b.side(out.x) == 0);
		assert(a.side(out.y) == 0 && b.side(out.y) == 0);

		// Test if arc is oriented CCW for a and CW for b.
		assert(b.side(between(a.p, out.x, out.y)) == 1);
		assert(a.side(between(b.p, out.y, out.x)) == 1);
	}
}

void circleLine(circle a, line b, int expected) {
	pair<vec, vec> out;
	assert(a.intersect(b, out) == expected);

	if (expected == 1) {
		assert(out.x == out.y);
		assert(a.side(out.x) == 0 && b.side(out.x) == 0);
	} else if (expected == 2) {
		assert(out.x != out.y);
		assert(a.side(out.x) == 0 && b.side(out.x) == 0);
		assert(a.side(out.y) == 0 && b.side(out.y) == 0);

		// Test if points are ordered according to norm.perp()
		assert(b.v.cross(out.x) < b.v.cross(out.y));
	}
}
#endif

void deterministic() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
	circle def;
	assert(def.p.x == 0 && def.p.y == 0 && def.r2 == 0);
#pragma GCC diagnostic pop

	assert(circle({4*U,2*U},25*U*U).side({1*U,7*U}) == -1);
	assert(circle({4*U,2*U},25*U*U).side({8*U,5*U}) == 0);
	assert(circle({4*U,2*U},25*U*U).side({7*U,5*U}) == 1);

#if FLOATING_POINT_GEOMETRY
	circleCircle({{4*U,2*U},25*U*U}, {{4*U,2*U},25*U*U}, 3);
	circleCircle({{4*U,2*U},25*U*U}, {{4*U,2*U},16*U*U}, 0);
	circleCircle({{4*U,2*U},25*U*U}, {{5*U,3*U},9*U*U}, 0);
	circleCircle({{4*U,2*U},25*U*U}, {{11*U,-2*U},9*U*U}, 0);
	circleCircle({{4*U,2*U},25*U*U}, {{11*U,-2*U},25*U*U}, 2);
	circleCircle({{4*U,2*U},25*U*U}, {{5*U,3*U},36*U*U}, 2);
	circleCircle({{4*U,2*U},25*U*U}, {{7*U,2*U},4*U*U}, 1);
	circleCircle({{4*U,2*U},25*U*U}, {{7*U,2*U},4*U*U}, 1);
	circleCircle({{4*U,2*U},25*U*U}, {{4*U,-5*U},4*U*U}, 1);

	circleLine({{6*U,3*U},16*U*U}, through({1*U,2*U},{4*U,-2*U}), 0);
	circleLine({{6*U,3*U},16*U*U}, through({2*U,7*U},{2*U,-2*U}), 1);
	circleLine({{6*U,3*U},16*U*U}, through({3*U,7*U},{5*U,-2*U}), 2);
	circleLine({{6*U,3*U},16*U*U}, through({5*U,-2*U},{3*U,7*U}), 2);
#endif
}

void fuzz() {
#if FLOATING_POINT_GEOMETRY
	rep(i, 0, 3e6) {
		vec p1 = randVecFromSquare(-1, 1);
		vec p2 = randVecFromSquare(-1, 1);

		int expected;
		double d = (p1-p2).len();
		double r2, r1 = randDouble(d/10, d*10);

		if (randBool()) {
			r2 = abs(d-r1);
			expected = 1;
		} else {
			r2 = randDouble(d/10, d*10);
			expected = (r1+r2 > d && d+r2 > r1 && d+r1 > r2 ? 2 : 0);
		}

		circle c1(p1, r1*r1), c2(p2, r2*r2);
		if (randBool()) swap(c1, c2);
		circleCircle(c1, c2, expected);
	}

	rep(i, 0, 3e6) {
		vec p1 = randVecFromSquare(-1, 1);
		vec p2 = randVecFromSquare(-1, 1);
		vec p3 = randVecFromSquare(-1, 1);
		auto area = (p3-p1).cross(p2-p1);
		if (area > 1e-2) {
			circle c = circum(p1, p2, p3);
			assert(!sgn(c.side(p1)));
			assert(!sgn(c.side(p2)));
			assert(!sgn(c.side(p3)));
		}
	}
#endif
}

void benchmark() {
}
