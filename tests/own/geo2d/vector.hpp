#pragma once
#include "../testing.hpp"
#include "../../../src/geo2d/vector.h"

#if FLOATING_POINT_GEOMETRY
#define U 0.1
#else
#define U 1
#endif

vec::T randCoord(double b, double e) {
	return vec::T(randDouble(b, e));
}

vec randVec(double b, double e) {
	return {randCoord(b, e), randCoord(b, e)};
}

bool isEqual(vec a, vec b) {
	return isEqual(a.x, b.x) && isEqual(a.y, b.y);
}

void deterministic() {
	assert(sgn(-3*U) == -1);
	assert(sgn(0) == 0);
	assert(sgn(3*U) == 1);
#if FLOATING_POINT_GEOMETRY
	assert(sgn(eps*2) == 1);
	assert(sgn(-eps*2) == -1);
	assert(sgn(eps) == 0);
	assert(sgn(-eps) == 0);
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
	vec a, b(3*U, 4*U);
	assert(a.x == 0 && a.y == 0);
	assert(b.x == 3*U && b.y == 4*U);
#pragma GCC diagnostic pop

	assert(isEqual(vec(1*U, 2*U) + vec(5*U, 10*U), vec(6*U, 12*U)));
	assert(isEqual(vec(1*U, 2*U) - vec(5*U, 10*U), vec(-4*U, -8*U)));
	assert(isEqual(vec(5*U, 6*U) * (3*U), vec(15*U*U, 18*U*U)));
	assert(isEqual(vec(6*U, 12*U) / -(3*U), vec(-2, -4)));

	assert(isEqual(vec(2*U, 5*U).dot(vec(10*U, 9*U)), 65*U*U));
	assert(isEqual(vec(2*U, 5*U).cross(vec(10*U, 9*U)), -32*U*U));
	assert(isEqual(vec(3*U, 4*U).len2(), 25*U*U));
	assert(isEqual(vec(3*U, 4*U).len(), 5.0*U));
	assert(isEqual(vec(1*U, 2*U).perp(), vec(-2*U, 1*U)));

	assert(isEqual(vec(5*U, 0*U).angle(), 0.0));
	assert(isEqual(vec(0*U, 5*U).angle(), M_PI/2));
	assert(isEqual(vec(-5*U, 0*U).angle(), M_PI));
	assert(isEqual(vec(0*U, -5*U).angle(), M_PI*3/2));
	assert(isEqual(vec(5*U, 5*U).angle(), M_PI/4));

	assert(vec(1*U, 2*U) == vec(1*U, 2*U));
	assert(!(vec(1*U, 2*U) == vec(2*U, 2*U)));
	assert(!(vec(1*U, 2*U) == vec(1*U, 1*U)));

	assert(vec(1*U, 2*U).cmpYX(vec(1*U, 2*U)) == 0);
	assert(vec(1*U, 2*U).cmpYX(vec(2*U, 2*U)) == -1);
	assert(vec(1*U, 2*U).cmpYX(vec(0*U, 3*U)) == -1);
	assert(vec(2*U, 2*U).cmpYX(vec(1*U, 2*U)) == 1);
	assert(vec(0*U, 3*U).cmpYX(vec(1*U, 2*U)) == 1);

	assert(vec(0*U, 0*U).upper());
	assert(vec(5*U, 0*U).upper());
	assert(vec(5*U, 5*U).upper());
	assert(vec(0*U, 5*U).upper());
	assert(vec(-5*U, 5*U).upper());

	assert(!vec(-5*U, 0*U).upper());
	assert(!vec(-5*U, -5*U).upper());
	assert(!vec(0*U, -5*U).upper());
	assert(!vec(5*U, -5*U).upper());

	vector<vec> sortedByAngle = {
		{123, 0}, {123, 1}, {5, 5}, {1, 100}, {0, 1},
		{-1, 100}, {-5, 5}, {-123, 1}, {-123, 0},
		{-123, -1}, {-5, -5}, {-1, -100}, {0, -1},
		{1, -100}, {5, -5}, {123, -1},
	};

	each(v, sortedByAngle) {
		v = v * U;
		assert(v.cmpAngle(v) == 0);
		assert(v.cmpAngle(v*2) == 0);
	}

	rep(i, 0, sz(sortedByAngle)) {
		rep(j, i+1, sz(sortedByAngle)) {
			assert(isLess(sortedByAngle[i].angle(), sortedByAngle[j].angle()));
			assert(sortedByAngle[i].cmpAngle(sortedByAngle[j]) == -1);
			assert(sortedByAngle[j].cmpAngle(sortedByAngle[i]) == 1);
		}
	}

#if FLOATING_POINT_GEOMETRY
	assert(isEqual(vec(0.5, 0.1).rotate(0), vec(0.5, 0.1)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI/2), vec(-0.1, 0.5)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI), vec(-0.5, -0.1)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI*3/2), vec(0.1, -0.5)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI*2), vec(0.5, 0.1)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI*20), vec(0.5, 0.1)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI*20.5), vec(-0.1, 0.5)));
	assert(isEqual(vec(0.5, 0.1).rotate(M_PI/4), vec(sqrt(2)*0.2, sqrt(2)*0.3)));
#endif
}

void fuzz() {
	rep(i, 0, 1e6) {
		vec a, b;
		do {
			a = randVec(-1e9, 1e9);
			if (randBool()) {
				b.x = randInt(-1, 1) * (randBool() ? a.x : a.y);
				b.y = randInt(-1, 1) * (randBool() ? a.x : a.y);
			} else {
				b = randVec(-1e9, 1e9);
			}
		} while (isEqual(a, vec(0, 0)) || isEqual(b, vec(0, 0)));
		assert(a.cmpAngle(b) == compare(a.angle(), b.angle()));
	}
}

void benchmark() {
	vec a = {1,2}, b = {7,5};
	measure("cmpAngle", 1e8, [&] {
		swap(a, b);
		consume(a.cmpAngle(b));
	});
}
