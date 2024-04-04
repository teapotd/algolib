#pragma once
#include "../template.h"

#ifndef GEO_COMMON_DEFINED //!HIDE
#define GEO_COMMON_DEFINED //!HIDE
// Scalar type: float or integer.
#if FLOATING_POINT_GEOMETRY
	using sc = double;
	constexpr sc eps = 1e-9;
#else
	using sc = ll;
	constexpr sc eps = 0;
#endif

// -1 if a < -eps, 1 if a > eps, 0 otherwise
int sgn(sc a) { return (a>eps) - (a < -eps); }
#endif //!HIDE

// 2D point/vector structure; UNIT-TESTED
struct vec {
	using P = vec;
	sc x = 0, y = 0;

	// The following methods are optional
	// and dependencies on them are noted
	// appropriately in library snippets.

	P operator+(P r) const {return{x+r.x,y+r.y};}
	P operator-(P r) const {return{x-r.x,y-r.y};}
	P operator*(sc r) const { return {x*r,y*r}; }
	P operator/(sc r) const { return {x/r,y/r}; }

	sc dot(P r)   const { return x*r.x + y*r.y; }
	sc cross(P r) const { return x*r.y - y*r.x; }
	sc len2()     const { return x*x + y*y; }
	double len()  const { return hypot(x, y); }
	P perp()      const { return {-y,x}; } // CCW

	double angle() const { //[0;2*PI] CCW from OX
		double a = atan2(y, x);
		return (a < 0 ? a+2*M_PI : a);
	}

	// Equality (with epsilon)
	bool operator==(vec r) const {
		return !sgn(x-r.x) && !sgn(y-r.y);
	}

	// Lexicographic compare by (y,x) (with eps)
	int cmpYX(P r) const {
		return sgn(y-r.y) ?: sgn(x-r.x);
	}

	// Is above OX or on its non-negative part?
	bool upper() const {
		return (sgn(y) ?: sgn(x)) >= 0;
	}

	// Compare vectors by angles.
	// Depends on: cross, upper
	int cmpAngle(P r) const {
		return r.upper()-upper() ?: -sgn(cross(r));
	}

#if FLOATING_POINT_GEOMETRY
	// Rotate counter-clockwise by given angle.
	P rotate(double a) const {
		return {x*cos(a) - y*sin(a),
		        x*sin(a) + y*cos(a)};
	}
#endif
};
