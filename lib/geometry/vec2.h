#pragma once
#include "../template.h"
#include "../util/float.h"
// UNTESTED

struct vec2 {
	using T = double;
	T x{0}, y{0};

	vec2() {}
	vec2(T a, T b) : x(a), y(b) {}

	vec2 operator+(vec2 r) const {
		return {x+r.x, y+r.y};
	}
	vec2 operator-(vec2 r) const {
		return {x-r.x, y-r.y};
	}
	vec2 operator*(T r) const {
		return {x*r, y*r};
	}
	vec2 operator/(T r) const {
		return {x/r, y/r};
	}

	T dot(vec2 r) const { return x*r.x+y*r.y; }
	T cross(vec2 r) const { return x*r.y-y*r.x; }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt(dist2()); }
	vec2 unit() const { return *this/dist(); }
	vec2 perp() const { return {-y, x}; }

	vec2 rotate(double a) const {
		return {x*cos(a) - y*sin(a),
			      x*sin(a) + y*cos(a)};
	}

	double angle() const {
		double a = atan2(y, x);
		return (a < 0 ? a+2*M_PI : a);
	}

	bool operator==(vec2 r) const {
		// For floats:
		return !cmp(x, r.x) && !cmp(y, r.y);
		// For integers:
		// return x == r.x && y == r.y;
	}

	bool operator<(vec2 r) const {
		// For doubles:
		int t = cmp(angle(), r.angle());
		return t < 0 || (!t && dist2()<r.dist2());
		// For integers:
		// if (upper()!=r.upper()) return upper();
		// auto t = cross(r);
		// return t>0 || (!t && dist2()<r.dist2());
	}

	bool upper() const {
		return y > 0 || (y == 0 && x > 0);
	}

	void print(...) { cerr << x << ',' << y; }
};
