#include "../../../src/geo2d/segment.h"
#include "../testing.h"
using namespace rel_ops;

void checkDist(seg s, vec p, ll distSqr) {
	assert(floatEqual(s.distTo(p), sqrt(distSqr)));
	assert(s.cmpDistTo(p, distSqr) == 0);
	assert(s.cmpDistTo(p, distSqr-1) == 1);
	assert(s.cmpDistTo(p, distSqr+1) == -1);
}

int main() {
	assert((seg{{1,5}, {7,7}}.contains({1,5})));
	assert((seg{{1,5}, {7,7}}.contains({4,6})));
	assert((seg{{1,5}, {7,7}}.contains({7,7})));
	assert((!seg{{1,5}, {7,7}}.contains({-2,4})));
	assert((!seg{{1,5}, {7,7}}.contains({10,8})));
	assert((!seg{{1,5}, {7,7}}.contains({5,6})));
	assert((!seg{{1,5}, {7,7}}.contains({2,5})));

	checkDist({{1,5}, {7,7}}, {0,5}, 1);
	checkDist({{1,5}, {7,7}}, {1,3}, 4);
	checkDist({{1,5}, {7,7}}, {8,6}, 2);
	checkDist({{1,5}, {7,7}}, {5,3}, 10);
	return 0;
}
