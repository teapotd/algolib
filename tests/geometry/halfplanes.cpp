#include "../../src/geometry/halfplanes.h"
#include "../testing.h"
using namespace rel_ops;

int main() {
	vector<line2> hplanes;

	hplanes.pb(line2::through({2,2}, {4,2}));
	hplanes.pb(line2::through({4,3}, {2,3}));
	hplanes.pb(line2::through({4,2}, {2,4}));
	hplanes.pb(line2::through({2,4}, {2,2}));

	// hplanes.pb(line2::through({6,3}, {5,1}));
	// hplanes.pb(line2::through({1,-1}, {-1,1}));

	// hplanes.pb(line2::through({7,2}, {5,5}));
	// hplanes.pb(line2::through({5,5}, {3,4}));
	// hplanes.pb(line2::through({3,4}, {4,1}));
	// hplanes.pb(line2::through({4,1}, {7,2}));

	// rep(i, 0, sz(hplanes)) {
	// 	auto a = hplanes[i], b = hplanes[(i+1)%sz(hplanes)];
	// 	vec2 p; assert(a.intersect(b, p));
	// 	deb(a, b, p);
	// }

	deb(hplanes);

	// hplanes.pb(line2::through({3,0}, {6,1}));
	// hplanes.pb(line2::through({5,15}, {3,14}));
	// hplanes.pb(line2::through({2,4}, {4,1}));
	// hplanes.pb(line2::through({4,-1}, {7,1}));

	shuffle(all(hplanes), rnd);

	vector<vec2> verts;
	int result = intersectHalfPlanes(hplanes, verts);

	deb(result);
	deb(verts);
}
