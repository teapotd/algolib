#pragma once
#include "../template.h"
#include "vector.h"

// Minkowski sum of given convex polygons.
// Points are expected to be in the same order
// as output from convexHull function; O(n+m)
// Depends on vec: +, -, cross, upper, cmpAngle
vector<vec> hullSum(const vector<vec>& A,
                    const vector<vec>& B) {
	int n = sz(A), m = sz(B), i = 0, j = 0;
	if (!n || !m) return {};
	vector<vec> C = {A[0]+B[0]};
	while (i+j < n+m) {
		vec a = A[(i+1)%n] - A[i%n];
		vec b = B[(j+1)%m] - B[j%m], v = C.back();
		int s = (i==n) - (j==m) ?: a.cmpAngle(b);
		if (s <= 0) v = v+a, i++;
		if (s >= 0) v = v+b, j++;
		C.pb(v);
	}
	C.pop_back();
	return C;
}
