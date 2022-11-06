#include "../../../src/geo2d/vector.h"
#include "../testing.h"
using namespace rel_ops;

bool floatEqual(double a, double b) {
	return fabs(a-b) < 1e-15;
}

int main() {
	vec a, b(3, 4);
	assert(a.x == 0 && a.y == 0);
	assert(b.x == 3 && b.y == 4);

	assert(vec(1, 2) == vec(1, 2));
	assert(vec(1, 2) != vec(2, 1));

	assert(!(vec(1, 2) < vec(1, 2)));
	assert(vec(1, 2) < vec(1, 3));
	assert(vec(1, 2) < vec(2, -1));
	assert(!(vec(1, 3) < vec(1, 2)));
	assert(!(vec(2, -1) < vec(1, 3)));

	assert(vec(1, 2) + vec(5, 10) == vec(6, 12));
	assert(vec(1, 2) - vec(5, 10) == vec(-4, -8));

	assert(vec(5, 6) * 3 == vec(15, 18));
	assert(vec(6, 12) / -3 == vec(-2, -4));

	assert(vec(2, 5).dot(vec(10, 9)) == 65);
	assert(vec(2, 5).cross(vec(10, 9)) == -32);
	assert(vec(3, 4).len2() == 25);
	assert(floatEqual(vec(3, 4).len(), 5));
	assert(vec(1, 2).perp() == vec(-2, 1));

	assert(floatEqual(vec(5, 0).angle(), 0));
	assert(floatEqual(vec(0, 5).angle(), M_PI/2));
	assert(floatEqual(vec(-5, 0).angle(), M_PI));
	assert(floatEqual(vec(0, -5).angle(), M_PI*3/2));
	assert(floatEqual(vec(5, 5).angle(), M_PI/4));

	assert(vec(0, 0).upper());
	assert(vec(50, 0).upper());
	assert(vec(50, 50).upper());
	assert(vec(0, 50).upper());
	assert(vec(-50, 50).upper());

	assert(!vec(-50, 0).upper());
	assert(!vec(-50, -50).upper());
	assert(!vec(0, -50).upper());
	assert(!vec(50, -50).upper());

	vector<vec> sorted = {
		{123, 0}, {123, 1}, {5, 5}, {1, 100}, {0, 1},
		{-1, 100}, {-5, 5}, {-123, 1}, {-123, 0},
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

	return 0;
}
