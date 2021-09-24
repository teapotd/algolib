#pragma once
#include "../template.h"
#include "modular.h"
#include "fft_mod.h"

//! Source: https://github.com/e-maxx-eng/e-maxx-eng-aux/blob/master/src/polynomial.cpp
using Poly = vector<Zp>;

// Cut off trailing zeroes; time: O(n)
void norm(Poly& P) {
	while (!P.empty() && !P.back().x)
		P.pop_back();
}

// Evaluate polynomial at x; time: O(n)
Zp eval(const Poly& P, Zp x) {
	Zp n = 0, y = 1;
	each(a, P) n += a*y, y *= x;
	return n;
}

// Add polynomial; time: O(n)
Poly& operator+=(Poly& l, const Poly& r) {
	l.resize(max(sz(l), sz(r)));
	rep(i, 0, sz(r)) l[i] += r[i];
	norm(l);
	return l;
}
Poly operator+(Poly l, const Poly& r) {
	return l += r;
}

// Subtract polynomial; time: O(n)
Poly& operator-=(Poly& l, const Poly& r) {
	l.resize(max(sz(l), sz(r)));
	rep(i, 0, sz(r)) l[i] -= r[i];
	norm(l);
	return l;
}
Poly operator-(Poly l, const Poly& r) {
	return l -= r;
}

// Multiply by polynomial; time: O(n lg n)
Poly& operator*=(Poly& l, const Poly& r) {
	if (min(sz(l), sz(r)) < 50) {
		// Naive multiplication
		Poly P(sz(l)+sz(r));
		rep(i, 0, sz(l)) rep(j, 0, sz(r))
			P[i+j] += l[i]*r[j];
		l.swap(P);
	} else {
		// FFT multiplication
		vector<ll> a, b;
		each(k, l) a.pb(k.x);
		each(k, r) b.pb(k.x);
		// Choose appropriate convolution method,
		// see fft_mod.h and fft_complex.h
		convolve<MOD, 62>(a, b);
		l.assign(all(a));
	}
	norm(l);
	return l;
}
Poly operator*(Poly l, const Poly& r) {
	return l *= r;
}

// Derivate polynomial; time: O(n)
Poly derivate(Poly P) {
	if (!P.empty()) {
		rep(i, 1, sz(P)) P[i-1] = P[i]*i;
		P.pop_back();
	}
	return P;
}

// Integrate polynomial; time: O(n)
Poly integrate(Poly P) {
	if (!P.empty()) {
		P.pb(0);
		for (int i = sz(P); --i;) P[i] = P[i-1]/i;
		P[0] = 0;
	}
	return P;
}

// Compute inverse series mod x^n; O(n lg n)
Poly invert(const Poly& P, int n) {
	assert(!P.empty() && P[0].x != 0);
	Poly tmp, ret = {P[0].inv()};

	for (int i = 1; i < n; i *= 2) {
		tmp.clear();
		rep(j, 0, min(i*2, sz(P))) tmp.pb(-P[j]);
		tmp *= ret;
		tmp[0] += 2;
		ret *= tmp;
		ret.resize(i*2);
	}

	ret.resize(n);
	return ret;
}

// Floor division by polynomial; O(n lg n)
Poly operator/(Poly l, Poly r) {
	norm(l); norm(r);
	int d = sz(l)-sz(r)+1;
	if (d <= 0) return {};
	reverse(all(l));
	reverse(all(r));
	l.resize(d);
	l *= invert(r, d);
	l.resize(d);
	reverse(all(l));
	return l;
}
Poly& operator/=(Poly& l, const Poly& r) {
	return l = l/r;
}

// Compute modulo by polynomial; O(n lg n)
Poly operator%(const Poly& l, const Poly& r) {
	return l - r*(l/r);
}
Poly& operator%=(Poly& l, const Poly& r) {
	return l -= r*(l/r);
}

// Compute a^e mod m, where a and m are
// polynomials; time: O(m log m log e)
Poly pow(Poly a, ll e, Poly m) {
	Poly t = {1};
	while (e) {
		if (e % 2) t = t*a % m;
		e /= 2; a = a*a % m;
	}
	return t;
}

// Evaluate polynomial P in given points;
// time: O(n lg^2 n)
Poly eval(const Poly& P, Poly points) {
	int len = 1;
	while (len < sz(points)) len *= 2;

	vector<Poly> tree(len*2, {1});
	rep(i, 0, sz(points))
		tree[len+i] = {-points[i], 1};

	for (int i = len; --i;)
		tree[i] = tree[i*2] * tree[i*2+1];

	tree[0] = P;
	rep(i, 1, len*2)
		tree[i] = tree[i/2] % tree[i];

	rep(i, 0, sz(points)) {
		auto& vec = tree[len+i];
		points[i] = vec.empty() ? 0 : vec[0];
	}
	return points;
}

// Given n points (x, f(x)) compute n-1-degree
// polynomial f that passes through them;
// time: O(n lg^2 n)
// For O(n^2) version see polynomial_interp.h.
Poly interpolate(const vector<pair<Zp,Zp>>& P){
	int len = 1;
	while (len < sz(P)) len *= 2;

	vector<Poly> mult(len*2, {1}), tree(len*2);
	rep(i, 0, sz(P))
		mult[len+i] = {-P[i].x, 1};

	for (int i = len; --i;)
		mult[i] = mult[i*2] * mult[i*2+1];

	tree[0] = derivate(mult[1]);
	rep(i, 1, len*2)
		tree[i] = tree[i/2] % mult[i];

	rep(i, 0, sz(P))
		tree[len+i][0] = P[i].y / tree[len+i][0];

	for (int i = len; --i;)
		tree[i] = tree[i*2]*mult[i*2+1]
		        + mult[i*2]*tree[i*2+1];
	return tree[1];
}
