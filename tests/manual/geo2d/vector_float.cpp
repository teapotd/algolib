#define FLOATING_POINT_GEOMETRY 1
#include "../../../src/geo2d/vector.h"
#include "../testing.h"
using namespace rel_ops;

bool vecEqual(vec a, vec b) {
	return floatEqual(a.x, b.x) && floatEqual(a.y, b.y);
}

int main() {
	assert(sgn(eps*2) == 1);
	assert(sgn(-eps*2) == -1);
	assert(sgn(eps) == 0);
	assert(sgn(-eps) == 0);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
	vec a, b(3.11, 4.67);
	assert(a.x == 0 && a.y == 0);
	assert(b.x == 3.11 && b.y == 4.67);
#pragma GCC diagnostic pop

	assert(vecEqual(vec(1.1, 2.5) + vec(5.1, 10), vec(6.2, 12.5)));
	assert(vecEqual(vec(1, 2.5) - vec(5.1, 10), vec(-4.1, -7.5)));
	assert(vecEqual(vec(5.5, 6) * 3, vec(16.5, 18)));
	assert(vecEqual(vec(5, 9) / -3, vec(-5.0/3, -9.0/3)));

	assert(floatEqual(vec(2.11, 5).dot(vec(10, 9)), 66.1));
	assert(floatEqual(vec(2, 5.11).cross(vec(10, 9)), -33.1));
	assert(floatEqual(vec(0.3, 0.4).len2(), 0.25));
	assert(floatEqual(vec(0.3, 0.4).len(), 0.5));
	assert(vecEqual(vec(1.5, 2.7).perp(), vec(-2.7, 1.5)));

	assert(floatEqual(vec(5.123, 0).angle(), 0));
	assert(floatEqual(vec(0, 5.123).angle(), M_PI/2));
	assert(floatEqual(vec(-5.123, 0).angle(), M_PI));
	assert(floatEqual(vec(0, -5.123).angle(), M_PI*3/2));
	assert(floatEqual(vec(5.123, 5.123).angle(), M_PI/4));

	assert(vec(0.01, 0.02).cmpYX(vec(0.01, 0.02)) == 0);
	assert(vec(0.01, 0.02).cmpYX(vec(0.02, 0.02)) == -1);
	assert(vec(0.01, 0.02).cmpYX(vec(0.00, 0.03)) == -1);
	assert(vec(0.02, 0.02).cmpYX(vec(0.01, 0.02)) == 1);
	assert(vec(0.00, 0.03).cmpYX(vec(0.01, 0.02)) == 1);

	assert(vec(0, 0).upper());
	assert(vec(50.123, 0).upper());
	assert(vec(50.123, 50).upper());
	assert(vec(0, 50.123).upper());
	assert(vec(-50.123, 50).upper());

	assert(!vec(-50.123, 0).upper());
	assert(!vec(-50, -50.123).upper());
	assert(!vec(0, -50.123).upper());
	assert(!vec(50.123, -50).upper());

	vector<vec> sortedByAngle = {
		{123.1, 0}, {123.5, 0.01}, {5.1, 5.77}, {1.01, 100.5}, {0, 1.0001},
		{-0.001, 98.3234}, {-5.3, 5.22}, {-123.433, 1.01}, {-123.1, 0},
		{-123, -1}, {-5, -5}, {-1, -100}, {0, -1},
		{1, -100}, {5, -5}, {123, -1},
	};

	each(v, sortedByAngle) {
		assert(v.cmpAngle(v) == 0);
		assert(v.cmpAngle(v*2) == 0);
	}

	rep(i, 0, sz(sortedByAngle)) {
		rep(j, i+1, sz(sortedByAngle)) {
			assert(sortedByAngle[i].cmpAngle(sortedByAngle[j]) == -1);
			assert(sortedByAngle[j].cmpAngle(sortedByAngle[i]) == 1);
		}
	}

	assert(vecEqual(vec(5, 1).rotate(0), vec(5, 1)));
	assert(vecEqual(vec(5, 1).rotate(M_PI/2), vec(-1, 5)));
	assert(vecEqual(vec(5, 1).rotate(M_PI), vec(-5, -1)));
	assert(vecEqual(vec(5, 1).rotate(M_PI*3/2), vec(1, -5)));
	assert(vecEqual(vec(5, 1).rotate(M_PI*2), vec(5, 1)));
	assert(vecEqual(vec(5, 1).rotate(M_PI*20), vec(5, 1)));
	assert(vecEqual(vec(5, 1).rotate(M_PI*20.5), vec(-1, 5)));
	assert(vecEqual(vec(5, 1).rotate(M_PI/4), vec(sqrt(2)*2, sqrt(2)*3)));

	rep(i, 0, 1000) {
		double scale = (i%2 ? 1 : 1e9);
		a = {rf(-scale, scale), rf(-scale, scale)};
		b = {rf(-scale, scale), rf(-scale, scale)};
		assert(a.cmpAngle(b) == sgn(a.angle()-b.angle()));
	}
	return 0;
}
