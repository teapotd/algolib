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

// 2D point/vector structure; UNIT-TESTED
struct vec {
	using P = vec;
#if FLOATING_POINT_GEOMETRY //!HIDE
	using T = double; // FLOATING_POINT_GEOMETRY
#else                       //!HIDE
	using T = ll;     // !FLOATING_POINT_GEOMETRY
#endif                      //!HIDE
	T x = 0, y = 0;

	// The following methods are optional
	// and dependencies on them are noted
	// appropriately in library snippets.

	P operator+(P r) const {return{x+r.x,y+r.y};}
	P operator-(P r) const {return{x-r.x,y-r.y};}
	P operator*(T r) const { return {x*r, y*r}; }
	P operator/(T r) const { return {x/r, y/r}; }

	T dot(P r)   const { return x*r.x + y*r.y; }
	T cross(P r) const { return x*r.y - y*r.x; }
	T len2()     const { return x*x + y*y; }
	double len() const { return hypot(x, y); }
	P perp()     const { return {-y,x}; } // CCW

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
