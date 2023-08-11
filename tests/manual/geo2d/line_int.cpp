#define FLOATING_POINT_GEOMETRY 0
#include "../../../src/geo2d/line.h"
#include "../testing.h"
using namespace rel_ops;

ll gcd(ll a, ll b) {
	while (b) a %= b, swap(a, b);
	return a;
}

line normGcd(line l) {
	ll g = gcd(gcd(abs(l.v.x), abs(l.v.y)), abs(l.c));
	l.v = l.v/g;
	l.c /= g;
	return l;
}

bool lineEqual(line a, line b) {
	a = normGcd(a);
	b = normGcd(b);
	return a.v == b.v && a.c == b.c;
}

int main() {
	assert(lineEqual(through({2,4}, {14,8}), {{1,-3},-10}));
	assert(lineEqual(through({14,8}, {2,4}), {{-1,3},10}));
	assert(lineEqual(parallel({8,6}, {{-10,30},-123}), {{-1,3},10}));
	assert(lineEqual(perp({8,6}, {{30,10},-123}), {{-1,3},10}));

	assert(floatEqual(line{{1,-3},-10}.distTo({8,6}), 0));
	assert(floatEqual(line{{1,-3},-10}.distTo({-5,5}), sqrt(10)));
	assert(floatEqual(line{{1,-3},-10}.distTo({3,1}), sqrt(10)));

	assert((line{{1,-3},-10}.side({8,6}) == 0));
	assert((line{{1,-3},-10}.side({-5,5}) == -1));
	assert((line{{1,-3},-10}.side({3,1}) == 1));

	return 0;
}
