#define FLOATING_POINT_GEOMETRY 0
#include "../../../src/geo2d/vector.h"
#include "../testing.h"

int cmpFloat(double a, double b, double eps = 1e-9) {
	return (a > b+eps) - (a+eps < b);
}

bool vecEqual(vec a, vec b) {
	return a.x == b.x && a.y == b.y;
}

int main() {
	assert(cmp(123, 122) > 0);
	assert(cmp(123, 123) == 0);
	assert(cmp(123, 124) < 0);

	vec a, b(3, 4);
	assert(a.x == 0 && a.y == 0);
	assert(b.x == 3 && b.y == 4);

	assert(vecEqual(vec(1, 2) + vec(5, 10), vec(6, 12)));
	assert(vecEqual(vec(1, 2) - vec(5, 10), vec(-4, -8)));
	assert(vecEqual(vec(5, 6) * 3, vec(15, 18)));
	assert(vecEqual(vec(6, 12) / -3, vec(-2, -4)));

	assert(vec(2, 5).dot(vec(10, 9)) == 65);
	assert(vec(2, 5).cross(vec(10, 9)) == -32);
	assert(vec(3, 4).len2() == 25);
	assert(floatEqual(vec(3, 4).len(), 5));
	assert(vecEqual(vec(1, 2).perp(), vec(-2, 1)));

	assert(floatEqual(vec(5, 0).angle(), 0));
	assert(floatEqual(vec(0, 5).angle(), M_PI/2));
	assert(floatEqual(vec(-5, 0).angle(), M_PI));
	assert(floatEqual(vec(0, -5).angle(), M_PI*3/2));
	assert(floatEqual(vec(5, 5).angle(), M_PI/4));

	assert(vec(1, 2).cmpYX(vec(1, 2)) == 0);
	assert(vec(1, 2).cmpYX(vec(2, 2)) == -1);
	assert(vec(1, 2).cmpYX(vec(0, 3)) == -1);
	assert(vec(2, 2).cmpYX(vec(1, 2)) == 1);
	assert(vec(0, 3).cmpYX(vec(1, 2)) == 1);

	assert(vec(0, 0).upper());
	assert(vec(50, 0).upper());
	assert(vec(50, 50).upper());
	assert(vec(0, 50).upper());
	assert(vec(-50, 50).upper());

	assert(!vec(-50, 0).upper());
	assert(!vec(-50, -50).upper());
	assert(!vec(0, -50).upper());
	assert(!vec(50, -50).upper());

	vector<vec> sortedByAngle = {
		{123, 0}, {123, 1}, {5, 5}, {1, 100}, {0, 1},
		{-1, 100}, {-5, 5}, {-123, 1}, {-123, 0},
		{-123, -1}, {-5, -5}, {-1, -100}, {0, -1},
		{1, -100}, {5, -5}, {123, -1},
	};

	each(v, sortedByAngle) {
		assert(v.cmpAngle(v) == 0);
		assert(v.cmpAngle(v*2) == 0);
	}

	rep(i, 0, sz(sortedByAngle)) {
		rep(j, i+1, sz(sortedByAngle)) {
			assert(sortedByAngle[i].cmpAngle(sortedByAngle[j]) < 0);
			assert(sortedByAngle[j].cmpAngle(sortedByAngle[i]) > 0);
		}
	}

	rep(i, 0, 1000) {
		a = {r(-1e9, 1e9), r(-1e9, 1e9)};
		b = {r(-1e9, 1e9), r(-1e9, 1e9)};
		assert(a.cmpAngle(b) == cmpFloat(a.angle(), b.angle()));
	}
	return 0;
}
