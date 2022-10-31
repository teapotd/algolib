#include "../../../src/geometry/convex_hull.h"
#include "../../../src/geometry/convex_hull_sum.h"
#include "../testing.h"
using namespace rel_ops;

vector<vec2> randPoints(int n) {
	vector<vec2> vec(n);
	each(v, vec) v = { rf(-1000, 1000), rf(-1000, 1000) };
	return vec;
}

int naiveMinDot(const vector<vec2>& hull, vec2 q) {
	pair<double, int> ret = { 1e30, 0 };
	rep(i, 0, sz(hull)) {
		ret = min(ret, make_pair(q.dot(hull[i]), i));
	}
	return ret.y;
}

void check(int n) {
	auto hull = convexHull(randPoints(n));

	rep(i, 0, 100) {
		vec2 q = { rf(-1000, 1000), rf(-1000, 1000) };

		int got = minDot(hull, q);
		int expected = naiveMinDot(hull, q);
		assert(got == expected);
	}
}

int main() {
	rep(i, 0, 100) {
		check(1000);
	}
}
