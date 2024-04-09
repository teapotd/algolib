#pragma once
#include "../template.h"

// NOTE: sc, eps, sgn as for vector 2D

// 3D point/vector structure; UNTESTED
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point3D.h
struct vec3 {
	using P = vec3;
	sc x = 0, y = 0, z = 0;

	// The following methods are optional
	// and dependencies on them are noted
	// appropriately in library snippets.

	P operator+(P r) const {
		return {x+r.x, y+r.y, z+r.z};
	}
	P operator-(P r) const {
		return {x-r.x, y-r.y, z-r.z};
	}
	P operator*(sc r) const {
		return {x*r, y*r, z*r};
	}
	P operator/(sc r) const {
		return {x/r, y/r, z/r};
	}
	sc dot(P r) const {
		return x*r.x + y*r.y + z*r.z;
	}
	P cross(P r) const {
		return {y*r.z - z*r.y, z*r.x - x*r.z,
		        x*r.y - y*r.x};
	}
	sc len2()    const { return x*x+y*y+z*z; }
	double len() const { return hypot(x,y,z); }

	// Equality (with epsilon)
	bool operator==(vec3 r) const {
		return !sgn(x-r.x) && !sgn(y-r.y) &&
		       !sgn(z-r.z);
	}

	// Angle between vectors in [0,2*PI]
	double angle(vec3 r) const {
		return atan2(cross(r).len(), dot(r));
	}

#if FLOATING_POINT_GEOMETRY
	// Rotate counter-clockwise around axis.
	P rotate(double angle, vec3 axis) const {
		auto s = sin(angle), c = cos(angle);
		P u = axis / axis.len();
		return u*dot(u)*(1-c)+(*this)*c-cross(u)*s;
	}
#endif
};
