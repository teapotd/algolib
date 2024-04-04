#pragma once
#include "../../../src/geo2d/segment.h"
#include "common.hpp"

void checkDist(seg s, vec p, sc distSqr) {
	assert(equalWithEps(s.dist(p), sqrt(distSqr)));
#if not FLOATING_POINT_GEOMETRY
	assert(s.cmpDist(p, distSqr) == 0);
	assert(s.cmpDist(p, distSqr-1*U) == 1);
	assert(s.cmpDist(p, distSqr+1*U) == -1);
#endif
}

void deterministic() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
	seg def;
	assert(def.a.x == 0 && def.a.y == 0 && def.b.x == 0 && def.b.y == 0);
#pragma GCC diagnostic pop

	assert((seg{{1*U,5*U}, {7*U,7*U}}.contains({1*U,5*U})));
	assert((seg{{1*U,5*U}, {7*U,7*U}}.contains({4*U,6*U})));
	assert((seg{{1*U,5*U}, {7*U,7*U}}.contains({7*U,7*U})));
	assert((!seg{{1*U,5*U}, {7*U,7*U}}.contains({-2*U,4*U})));
	assert((!seg{{1*U,5*U}, {7*U,7*U}}.contains({10*U,8*U})));
	assert((!seg{{1*U,5*U}, {7*U,7*U}}.contains({5*U,6*U})));
	assert((!seg{{1*U,5*U}, {7*U,7*U}}.contains({2*U,5*U})));

	assert((seg{{1*U,5*U}, {7*U,7*U}}.side({0*U,5*U}) == 1));
	assert((seg{{1*U,5*U}, {7*U,7*U}}.side({1*U,3*U}) == -1));
	assert((seg{{1*U,5*U}, {7*U,7*U}}.side({-5*U,3*U}) == 0));

	checkDist({{1*U,5*U}, {7*U,7*U}}, {0*U,5*U}, 1*U*U);
	checkDist({{1*U,5*U}, {7*U,7*U}}, {1*U,3*U}, 4*U*U);
	checkDist({{1*U,5*U}, {7*U,7*U}}, {8*U,6*U}, 2*U*U);
	checkDist({{1*U,5*U}, {7*U,7*U}}, {5*U,3*U}, 10*U*U);

	checkDist({{1*U,5*U}, {1*U,5*U}}, {5*U, 5*U}, 16*U*U);
	checkDist({{1*U,5*U}, {1*U,5*U}}, {1*U, 5*U}, 0*U*U);
}

void fuzz() {
}

void benchmark() {
}
