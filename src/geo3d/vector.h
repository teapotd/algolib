#pragma once
#include "../template.h"

// Sign extraction, type in the one you need.
// -1 if a < -eps, 1 if a > eps, 0 otherwise
#if FLOATING_POINT_GEOMETRY
	constexpr double eps = 1e-9;
	int sgn(double a) {
		return (a > eps) - (a < -eps);
	}
#else // (integers)
	int sgn(ll a) { return (a > 0) - (a < 0); }
#endif

// 3D point/vector structure; UNTESTED
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point3D.h
struct vec {
	using P = vec;
#if FLOATING_POINT_GEOMETRY //!HIDE
	using T = double; // FLOATING_POINT_GEOMETRY
#else                       //!HIDE
	using T = ll;     // !FLOATING_POINT_GEOMETRY
#endif                      //!HIDE
	T x = 0, y = 0, z = 0;

	// The following methods are optional
	// and dependencies on them are noted
	// appropriately in library snippets.

	P operator+(P r) const {
		return {x+r.x, y+r.y, z+r.z};
	}
	P operator-(P r) const {
		return {x-r.x, y-r.y, z-r.z};
	}
	P operator*(T r) const {return{x*r,y*r,z*r};}
	P operator/(T r) const {return{x/r,y/r,z/r};}

	T dot(P r) const {
		return x*r.x + y*r.y + z*r.z;
	}

	P cross(P r) const {
		return {y*r.z - z*r.y, z*r.x - x*r.z,
		        x*r.y - y*r.x};
	}

	T len2()     const { return x*x+y*y+z*z; }
	double len() const { return hypot(x,y,z); }

	// Equality (with epsilon)
	bool operator==(vec r) const {
		return !sgn(x-r.x) && !sgn(y-r.y) &&
		       !sgn(z-r.z);
	}

#if FLOATING_POINT_GEOMETRY
	// Rotate counter-clockwise around axis.
	P rotate(double angle, vec axis) const {
		auto s = sin(angle), c = cos(angle);
		P u = axis / axis.len();
		return u*dot(u)*(1-c)+(*this)*c-cross(u)*s;
	}
#endif
};
