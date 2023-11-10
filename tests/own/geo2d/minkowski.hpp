#pragma once
#include "../../../src/geo2d/minkowski.h"
#include "../../../src/geo2d/convex_hull.h"
#include "../testing.hpp"

vec randFromDisk(double R) {
	double r = sqrt(randDouble()) * R;
	double a = randDouble(0, M_PI*2);
	double x = r * cos(a), y = r * sin(a);
	return {vec::T(x), vec::T(y)};
}

vector<vec> randFromDisk(int n, double R) {
	vector<vec> vec(n);
	each(v, vec) v = randFromDisk(R);
	return vec;
}

vector<vec> naiveHullSum(vector<vec>& A, vector<vec>& B) {
	vector<vec> sum;
	each(v, A) each(u, B) sum.pb(v+u);
	return convexHull(sum);
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 50000) {
		auto A = convexHull(randFromDisk(randInt(0, 50), randDouble(1, 50)));
		auto B = convexHull(randFromDisk(randInt(0, 50), randDouble(1, 50)));
		auto fast = hullSum(A, B);
		auto naive = naiveHullSum(A, B);
		assert(fast == naive);
	}
}

void benchmark() {
}
