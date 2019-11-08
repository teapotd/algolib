#include "../../src/geometry/convex_hull.h"
#include "../../src/geometry/convex_hull_sum.h"
#include "../testing.h"
using namespace rel_ops;

vector<vec2> randPoints(int n) {
	vector<vec2> vec(n);
	each(v, vec) v = { rf(-1000, 1000), rf(-1000, 1000) };
	return vec;
}

vector<vec2> naiveHullSum(vector<vec2>& A, vector<vec2>& B) {
	vector<vec2> sum;
	each(v, A) each(u, B) sum.pb(v+u);
	return convexHull(sum);
}

int main() {
	auto hull1 = convexHull(randPoints(1000));
	auto hull2 = convexHull(randPoints(1000));

	auto naive = naiveHullSum(hull1, hull2);
	auto fast = hullSum(hull1, hull2);

	assert(sz(naive) == sz(fast));

	rep(i, 0, sz(naive)) {
		assert(naive[i] == fast[i]);
	}
}
