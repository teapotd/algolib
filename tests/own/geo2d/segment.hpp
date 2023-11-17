#pragma once
#include "../../../src/geo2d/segment.h"
#include "common.hpp"

void checkDist(seg s, vec p, vec::T distSqr) {
	assert(equalWithEps(s.distTo(p), sqrt(distSqr)));
#if not FLOATING_POINT_GEOMETRY
	assert(s.cmpDistTo(p, distSqr) == 0);
	assert(s.cmpDistTo(p, distSqr-1*U) == 1);
	assert(s.cmpDistTo(p, distSqr+1*U) == -1);
#endif
}

void deterministic() {
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
