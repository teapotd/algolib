#define FLOATING_POINT_GEOMETRY 1
#include "../../../src/geo2d/line.h"
#include "../testing.h"
using namespace rel_ops;

line norm(line l) {
	auto g = l.v.len();
	l.v = l.v/g;
	l.c /= g;
	return l;
}

bool lineEqual(line a, line b) {
	a = norm(a);
	b = norm(b);
	return a.v == b.v && cmp(a.c, b.c) == 0;
}

int main() {
	assert(lineEqual(through({0.2,0.4}, {1.4,0.8}), {{1,-3},-1}));
	assert(lineEqual(through({1.4,0.8}, {0.2,0.4}), {{-1,3},1}));
	assert(lineEqual(parallel({0.8,0.6}, {{-0.1,0.3},-12.3}), {{-1,3},1}));
	assert(lineEqual(perp({0.8,0.6}, {{0.3,0.1},-12.3}), {{-1,3},1}));

	assert(floatEqual(line{{1,-3},-1}.distTo({0.8,0.6}), 0));
	assert(floatEqual(line{{1,-3},-1}.distTo({-0.5,0.5}), sqrt(0.1)));
	assert(floatEqual(line{{1,-3},-1}.distTo({0.3,0.1}), sqrt(0.1)));

	assert((line{{1,-3},-1}.side({0.8,0.6}) == 0));
	assert((line{{1,-3},-1}.side({-0.5,0.5}) == -1));
	assert((line{{1,-3},-1}.side({0.3,0.1}) == 1));

	vec inter;
	assert(!(line{{1,-3},-10}.intersect({{1,-3},-11}, inter)));
	assert(!(line{{1,-3},-10}.intersect({{-1,3},-11}, inter)));

	assert((line{{0.5,1},7.5}.intersect({{1,-3},-10}, inter)));
	assert(inter == vec(5,5));
	return 0;
}
