#define FLOATING_POINT_GEOMETRY 1
#include "../../../src/geo2d/segment.h"
#include "../testing.h"
using namespace rel_ops;

void checkDist(seg s, vec p, double distSqr) {
	assert(floatEqual(s.distTo(p), sqrt(distSqr)));
}

int main() {
	assert((seg{{0.1,0.5}, {0.7,0.7}}.contains({0.1,0.5})));
	assert((seg{{0.1,0.5}, {0.7,0.7}}.contains({0.4,0.6})));
	assert((seg{{0.1,0.5}, {0.7,0.7}}.contains({0.7,0.7})));
	assert((!seg{{0.1,0.5}, {0.7,0.7}}.contains({-0.2,0.4})));
	assert((!seg{{0.1,0.5}, {0.7,0.7}}.contains({0.10,0.8})));
	assert((!seg{{0.1,0.5}, {0.7,0.7}}.contains({0.5,0.6})));
	assert((!seg{{0.1,0.5}, {0.7,0.7}}.contains({0.2,0.5})));

	checkDist({{0.1,0.5}, {0.7,0.7}}, {0.0,0.5}, 0.01);
	checkDist({{0.1,0.5}, {0.7,0.7}}, {0.1,0.3}, 0.04);
	checkDist({{0.1,0.5}, {0.7,0.7}}, {0.8,0.6}, 0.02);
	checkDist({{0.1,0.5}, {0.7,0.7}}, {0.5,0.3}, 0.1);
	return 0;
}
