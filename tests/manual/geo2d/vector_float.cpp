#define FLOATING_POINT_GEOMETRY
#include "../../../src/geo2d/vector.h"
#include "../testing.h"
using namespace rel_ops;

bool floatEqual(double a, double b) {
	return fabs(a-b) < 1e-15;
}

int main() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
	vec a, b(3.11, 4.67);
	assert(a.x == 0 && a.y == 0);
	assert(b.x == 3.11 && b.y == 4.67);
#pragma GCC diagnostic pop

	assert(vec(1.1, 2.99) == vec(1.1, 2.99));
	assert(vec(1.1, 2.99) != vec(2.99, 1.1));

	assert(!(vec(0.01, 0.02) < vec(0.01, 0.02)));
	assert(vec(0.01, 0.02) < vec(0.01, 0.03));
	assert(vec(0.01, 0.02) < vec(0.02, -0.01));
	assert(!(vec(0.01, 0.03) < vec(0.01, 0.02)));
	assert(!(vec(0.02, -0.01) < vec(0.01, 0.03)));

	assert(vec(1.1, 2.5) + vec(5.1, 10) == vec(6.2, 12.5));
	assert(vec(1, 2.5) - vec(5.1, 10) == vec(-4.1, -7.5));

	assert(vec(5.5, 6) * 3 == vec(16.5, 18));
	assert(vec(5, 9) / -3 == vec(5.0/-3, 9.0/-3));

	assert(floatEqual(vec(2.11, 5).dot(vec(10, 9)), 66.1));
	assert(floatEqual(vec(2, 5.11).cross(vec(10, 9)), -33.1));
	assert(floatEqual(vec(0.3, 0.4).len2(), 0.25));
	assert(floatEqual(vec(0.3, 0.4).len(), 0.5));
	assert(vec(1.5, 2.7).perp() == vec(-2.7, 1.5));

	assert(floatEqual(vec(5.123, 0).angle(), 0));
	assert(floatEqual(vec(0, 5.123).angle(), M_PI/2));
	assert(floatEqual(vec(-5.123, 0).angle(), M_PI));
	assert(floatEqual(vec(0, -5.123).angle(), M_PI*3/2));
	assert(floatEqual(vec(5.123, 5.123).angle(), M_PI/4));

	assert(vec(0, 0).upper());
	assert(vec(50.123, 0).upper());
	assert(vec(50.123, 50).upper());
	assert(vec(0, 50.123).upper());
	assert(vec(-50.123, 50).upper());

	assert(!vec(-50.123, 0).upper());
	assert(!vec(-50, -50.123).upper());
	assert(!vec(0, -50.123).upper());
	assert(!vec(50.123, -50).upper());

	vector<vec> sorted = {
		{123.1, 0}, {123.5, 0.01}, {5.1, 5.77}, {1.01, 100.5}, {0, 1.0001},
		{-0.001, 98.3234}, {-5.3, 5.22}, {-123.433, 1.01}, {-123.1, 0},
		{-123, -1}, {-5, -5}, {-1, -100}, {0, -1},
		{1, -100}, {5, -5}, {123, -1},
	};

	each(v, sorted) {
		assert(v.angleCmp(v) == 0);
		assert(v.angleCmp(v*2) == 0);
	}

	rep(i, 0, sz(sorted)) {
		rep(j, i+1, sz(sorted)) {
			assert(sorted[i].angleCmp(sorted[j]) < 0);
			assert(sorted[j].angleCmp(sorted[i]) > 0);
		}
	}

	assert(vec(5, 1).rotate(0) == vec(5, 1));
	assert(vec(5, 1).rotate(M_PI/2) == vec(-1, 5));
	assert(vec(5, 1).rotate(M_PI) == vec(-5, -1));
	assert(vec(5, 1).rotate(M_PI*3/2) == vec(1, -5));
	assert(vec(5, 1).rotate(M_PI*2) == vec(5, 1));
	assert(vec(5, 1).rotate(M_PI*20) == vec(5, 1));
	assert(vec(5, 1).rotate(M_PI*20.5) == vec(-1, 5));
	assert(vec(5, 1).rotate(M_PI/4) == vec(sqrt(2)*2, sqrt(2)*3));

	assert(cmp(123, 123+eps*2) < 0);
	assert(cmp(123, 123-eps*2) > 0);
	assert(cmp(123, 123+eps/2) == 0);
	assert(cmp(123, 123-eps/2) == 0);

	rep(i, 0, 100) {
		a = {rf(-1e9, 1e9), rf(-1e9, 1e9)};
		b = {rf(-1e9, 1e9), rf(-1e9, 1e9)};
		assert((a.angleCmp(b) < 0) == (a.angle() < b.angle()));
	}

	rep(i, 0, 100) {
		a = {rf(-1, 1), rf(-1, 1)};
		b = {rf(-1, 1), rf(-1, 1)};
		assert((a.angleCmp(b) < 0) == (a.angle() < b.angle()));
	}
	return 0;
}
