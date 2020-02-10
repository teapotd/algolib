#pragma once
#include "../template.h"
#include "modular.h"
#include "fft_mod.h"

// UNTESTED
using Poly = vector<Zp>;

// Cut off trailing zeroes; time: O(n)
void norm(Poly& P) {
	while (!P.empty() && !P.back().x)
		P.pop_back();
}

// Evaluate polynomial at x; time: O(n)
Zp eval(Poly& P, Zp x) {
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

// Multiply by polynomial;
// time: O(n lg n) if using FFT
Poly& operator*=(Poly& l, const Poly& r) {
	if (sz(l)*sz(r) < 200) {
		// Naive multiplication
		Poly P(sz(l)+sz(r)-1);
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
		convLong(a, b);
		l.assign(all(a));
	}
	norm(l);
	return l;
}
Poly operator*(Poly l, const Poly& r) {
	return l *= r;
}

// Derivate polynomial; time: O(n)
void derivate(Poly& P) {
	if (!P.empty()) {
		rep(i, 1, sz(P)) P[i-1] = P[i]*i;
		P.pop_back();
	}
}

// Integrate polynomial; time: O(n)
void integrate(Poly& P) {
	if (!P.empty()) {
		P.pb(0);
		for (int i = sz(P); --i;) P[i] = P[i-1]/i;
		P[0] = 0;
	}
}
