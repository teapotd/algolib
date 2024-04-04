#pragma once
#include "../../../src/geo3d/convex_hull.h"
#include "common.hpp"

void deterministic() {
}

void fuzz() {
}

void benchmark() {
	auto points = randVecsFromBall(1e5, 1e5-10, 1e5);

	measure("convexHull N=1e5", 1, [&] {
		auto hull = convexHull(points);
		deb(sz(hull));
		consume(&hull);
	});
}
