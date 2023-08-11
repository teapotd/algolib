#define FLOATING_POINT_GEOMETRY 0
#include "../../../src/geo2d/convex_hull.h"
#include "../../../src/geo2d/minkowski.h"
#include "../testing.h"

vector<vec> randPoints(int n) {
	vector<vec> vec(n);
	each(v, vec) v = { r(-50, 50), r(-50, 50) };
	return vec;
}

vector<vec> naiveHullSum(vector<vec>& A, vector<vec>& B) {
	vector<vec> sum;
	each(v, A) each(u, B) sum.pb(v+u);
	return convexHull(sum);
}

int main() {
	while (true) {
		auto hull1 = convexHull(randPoints(r(0, 100)));
		auto hull2 = convexHull(randPoints(r(0, 100)));

		auto naive = naiveHullSum(hull1, hull2);
		auto fast = hullSum(hull1, hull2);

		deb(naive);
		deb(fast);
		assert(fast == naive);
	}
}
