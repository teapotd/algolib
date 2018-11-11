#pragma once
#include "../template.h"
#include "vec2.h"

// Get edge sequence for given polygon
// starting from lower-left vertex; time: O(n)
// Returns start position.
vec2 edgeSeq(vector<vec2> points,
             vector<vec2>& edges) {
	int i = 0, n = sz(points);
	rep(j, 0, n) {
		if (points[i].yxPair()>points[j].yxPair())
			i = j;
	}
	rep(j, 0, n) edges.pb(points[(i+j+1)%n] -
	                      points[(i+j)%n]);
	return points[i];
}

// Minkowski sum of given convex polygons.
// Vertices are required to be in
// counter-clockwise order; time: O(n+m)
vector<vec2> hullSum(vector<vec2> A,
                     vector<vec2> B) {
	vector<vec2> sum, e1, e2, es(sz(A) + sz(B));
	vec2 pivot = edgeSeq(A, e1) + edgeSeq(B, e2);
	merge(all(e1), all(e2), es.begin());

	sum.pb(pivot);
	each(e, es) sum.pb(sum.back() + e);
	sum.pop_back();
	return sum;
}
