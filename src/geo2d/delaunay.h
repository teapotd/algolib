#include "../template.h"
#include "vector.h"
#include "../geo3d/convex_hull.h"

// Delaunay triangulation using 3D convex hull.
// Faces are in CCW order. Doesn't work if
// all points are colinear or on a same circle!
// time and memory: O(n log n)
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/DelaunayTriangulation.h
vector<Triple> delaunay(vector<vec>& p) {
	assert(sz(p) >= 3);
	if (sz(p) == 3) {
		int d = ((p[1]-p[0]).cross(p[2]-p[0]) < 0);
		return {{0, 1+d, 2-d}};
	}

	vector<vec3> p3;
	each(e, p) p3.pb({e.x, e.y, e.len2()});

	auto hull = convexHull(p3);
	erase_if(hull, [&](auto& t) {
		vec a = p[t[0]], b = p[t[1]], c = p[t[2]];
		swap(t[1], t[2]);
		return (b-a).cross(c-a) > 0;
	});
	return hull;
}
