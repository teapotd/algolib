#pragma once
#include "../template.h"

// Wrapper for scalars comparison:
// - floating point with epsilon or
// - exact integer comparisons.
// Type in only the one that you need.
// Returns -1 if a < b; 1 if a > b; 0 if equal
#if FLOATING_POINT_GEOMETRY
	// a and b are equal iff |a-b| <= eps
	constexpr double eps = 1e-9;
	int cmp(double a, double b) {
		return (a > b+eps) - (a+eps < b);
	}
#else // (integers)
	int cmp(ll a, ll b) {
		return (a > b) - (a < b);
	}
#endif

// 2D point/vector structure; UNIT-TESTED
struct vec {
	using P = vec;
#if FLOATING_POINT_GEOMETRY //!HIDE
	using T = double; // FLOATING_POINT_GEOMETRY
#else                       //!HIDE
	using T = ll;     // !FLOATING_POINT_GEOMETRY
#endif                      //!HIDE
	T x, y;
	vec(T a = 0, T b = 0) : x(a), y(b) {}

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

	// Lexicographic less (with epsilon)
	bool operator<(vec r) const {
		return (cmp(x, r.x) ?: cmp(y, r.y)) < 0;
	}

	// Equality (with epsilon)
	bool operator==(vec r) const {
		return !cmp(x, r.x) && !cmp(y, r.y);
	}

	// Is above OX or on its non-negative part?
	bool upper() const {
		return (cmp(y, 0) ?: cmp(x, 0)) >= 0;
	}

	// Compare vectors by angles.
	// Depends on: cross, upper
	int angleCmp(P r) const {
		return
			r.upper() - upper() ?: cmp(0, cross(r));
	}

#if FLOATING_POINT_GEOMETRY
	// Rotate counter-clockwise by given angle.
	P rotate(double a) const {
		return {x*cos(a) - y*sin(a),
		        x*sin(a) + y*cos(a)};
	}
#endif
};
