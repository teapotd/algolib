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

	T dot(S r)   const { return x*r.x+y*r.y; }
	T cross(S r) const { return x*r.y-y*r.x; }
	T len2()     const { return x*x + y*y; }
	double len() const { return sqrt(len2()); }
	S perp()     const { return {-y,x}; } //90deg

	pair<T, T> yxPair() const { return {y,x}; }

	double angle() const { //[0;2*PI] CCW from OX
		double a = atan2(y, x);
		return (a < 0 ? a+2*M_PI : a);
	}
};

// Version for integer coordinates (long long)
struct vec2i : bvec2<ll, vec2i> {
	vec2i() : bvec2{0, 0} {}
	vec2i(ll a, ll b) : bvec2{a, b} {}

	bool operator==(vec2i r) const {
		return x == r.x && y == r.y;
	}

	// Compare by angle, length if angles equal
	bool operator<(vec2i r) const {
		if (upper() != r.upper()) return upper();
		auto t = cross(r);
		return t > 0 || (!t && len2() < r.len2());
	}

	bool upper() const {
		return y > 0 || (y == 0 && x >= 0);
	}
};

// Version for double coordinates
// Requires cmp() from template
struct vec2d : bvec2<double, vec2d> {
	vec2d() : bvec2{0, 0} {}
	vec2d(double a, double b) : bvec2{a, b} {}

	vec2d unit() const { return *this/len(); }
	vec2d rotate(double a) const { // CCW
		return {x*cos(a) - y*sin(a),
			      x*sin(a) + y*cos(a)};
	}

	bool operator==(vec2d r) const {
		return !cmp(x, r.x) && !cmp(y, r.y);
	}

	// Compare by angle, length if angles equal
	bool operator<(vec2d r) const {
		int t = cmp(angle(), r.angle());
		return t < 0 || (!t && len2()<r.len2());
	}
};

using vec2 = vec2d;
