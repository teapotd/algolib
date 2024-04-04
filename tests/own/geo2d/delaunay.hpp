#pragma once
#include "../../../src/geo2d/delaunay.h"
#include "common.hpp"

void deterministic() {
}

void fuzz() {
}

void benchmark() {
	auto points = randVecsFromSquare(1e5, 1e4-10, 1e4);

	measure("delaunay N=1e5", 1, [&] {
		auto faces = delaunay(points);
		deb(sz(faces));
		consume(&faces);
	});
}
