#pragma once
#include "../template.h"
#include "vector.h"
#include "line.h" // For line intersections.

// 3D sphere structure; UNTESTED
//! Source: https://victorlecomte.com/cp-geo.pdf
struct sphere {
	vec3 p;    // Center
	sc r2 = 0; // Squared radius
	DBP(p, r2);

	// Returns -1 if point q lies outside sphere,
	// 0 if on the edge, 1 if strictly inside.
	// Depends on vec3: -, len2
	int side(vec3 a) {
		return sgn(r2 - (p-a).len2());
	}

#if FLOATING_POINT_GEOMETRY
	// Intersect with line.
	// Returns number of intersection points.
	// Points are in order given by direction.
	int intersect(line3 a, pair<vec3,vec3>& out){
		sc d = a.dist(p), h2 = r2 - d*d;
		vec3 h, t = a.proj(p);
		int s = sgn(h2)+1;
		if (s > 1) h = a.d * sqrt(h2 / a.d.len2());
		out = {t-h, t+h};
		return s;
	}
#endif
};
