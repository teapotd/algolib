#pragma once
#include "../../../src/geo2d/minkowski.h"
#include "../../../src/geo2d/convex_hull.h"
#include "common.hpp"

vector<vec> naiveHullSum(const vector<vec>& A, const vector<vec>& B) {
	vector<vec> sum;
	each(v, A) each(u, B) sum.pb(v+u);
	return convexHull(sum);
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 50'000) {
		double minR = randDouble(1, 50), maxR = randDouble(1, 50);
		if (minR > maxR) swap(minR, maxR);
		auto A = convexHull(randVecsFromDisk(randInt(0, 50), minR, maxR));
		auto B = convexHull(randVecsFromDisk(randInt(0, 50), minR, maxR));
		auto fast = hullSum(A, B);
		auto naive = naiveHullSum(A, B);
		assert(fast == naive);
	}
}

void benchmark() {
}
