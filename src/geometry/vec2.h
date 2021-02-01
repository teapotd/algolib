#pragma once
#include "../template.h"

// 2D point/vector structure; PARTIALLY TESTED

// Base class of versions for ints and doubles
template<class T, class S> struct bvec2 {
	T x, y;
	S operator+(S r) const {return{x+r.x,y+r.y};}
	S operator-(S r) const {return{x-r.x,y-r.y};}
	S operator*(T r) const { return {x*r, y*r}; }
	S operator/(T r) const { return {x/r, y/r}; }

	T dot(S r)   const { return x*r.x + y*r.y; }
	T cross(S r) const { return x*r.y - y*r.x; }
	T len2()     const { return x*x + y*y; }
	double len() const { return hypot(x, y); }
	S perp()     const { return {-y,x}; } // CCW

	pair<T, T> yx() const { return {y, x}; }

	double angle() const { //[0;2*PI] CCW from OX
		double a = atan2(y, x);
		return (a < 0 ? a+2*M_PI : a);
	}
};

// Version for integer coordinates (long long)
struct vec2i : bvec2<ll, vec2i> {
	vec2i() : bvec2{0, 0} {}
	vec2i(ll a, ll b) : bvec2{a, b} {}

	bool upper() const { return (y ?: x) >= 0; }

	int angleCmp(vec2i r) const {
		ll c = cross(r);
		return r.upper()-upper() ?: (c<0) - (c>0);
	}

	// Compare by angle, length if angles equal
	bool operator<(vec2i r) const {
		return (angleCmp(r) ?:
		        len2() - r.len2()) < 0;
	}

	bool operator==(vec2i r) const {
		return x == r.x && y == r.y;
	}
};

// Version for double coordinates
// Requires cmp() from template
struct vec2d : bvec2<double, vec2d> {
	vec2d() : bvec2{0, 0} {}
	vec2d(double a, double b) : bvec2{a, b} {}

	bool upper() const {
		return (cmp(y, 0) ?: cmp(x, 0)) >= 0;
	}

	int angleCmp(vec2d r) const {
		return r.upper() - upper() ?:
		       cmp(0, cross(r));
	}

	// Compare by angle, length if angles equal
	bool operator<(vec2d r) const {
		return (angleCmp(r) ?:
		        cmp(len2(), r.len2())) < 0;
	}

	bool operator==(vec2d r) const {
		return !cmp(x, r.x) && !cmp(y, r.y);
	}

	vec2d unit() const { return *this / len(); }

	vec2d rotate(double a) const { // CCW
		return {x*cos(a) - y*sin(a),
		        x*sin(a) + y*cos(a)};
	}
};

using vec2 = vec2d;
