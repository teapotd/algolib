#pragma once
#include "../template.h"
#include "vector.h"

// Signed volume of a polyhedron; UNTESTED
// Faces orientation needs to be consistent.
// Depends on vec3: cross, dot
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/PolyhedronVolume.h
double volume(vector<vec3>& p, auto& faces) {
	double v = 0;
	for (auto [a, b, c] : faces)
		v += double(p[a].cross(p[b]).dot(p[c]));
	return v / 6;
}
