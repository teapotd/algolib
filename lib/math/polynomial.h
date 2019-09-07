#pragma once
#include "../template.h"
#include "modular.h"
#include "fft_mod.h"

//!!IGNORE
// Polynomial wrapper class; UNTESTED
struct Poly {
	using T = Zp; // Set appropriate type
	vector<T> C;

	Poly(int n = 0) { C.resize(n); }

	// Cut off trailing zeroes
	void reduce() {
		// Change here `.x` if not using Zp
		while (!C.empty() && C.back().x == 0)
			C.pop_back();
	}

	// Evaluate polynomial at x; time: O(n)
	T eval(T x) {
		T n = 0, y = 1;
		each(a, C) n += a*y, y *= x;
		return n;
	}

	// Add polynomial; time: O(n)
	Poly& operator+=(const Poly& r) {
		C.resize(max(sz(C), sz(r.C)));
		rep(i, 0, sz(r.C)) C[i] += r.C[i];
		reduce();
		return *this;
	}

	// Subtract polynomial; time: O(n)
	Poly& operator-=(const Poly& r) {
		C.resize(max(sz(C), sz(r.C)));
		rep(i, 0, sz(r.C)) C[i] -= r.C[i];
		reduce();
		return *this;
	}

	// Multiply by polynomial
	// time: O(n lg n) if using FFT
	Poly operator*(const Poly& r) const {
		int len = sz(C) + sz(r.C) - 1;
		Poly ret;
		ret.C.resize(len);

		if (sz(C)*sz(r.C) < 200) {
			// If you don't need FFT - use just this
			rep(i, 0, sz(C)) rep(j, 0, sz(r.C)) {
				ret.C[i+j] = ret.C[i+j] + C[i]*r.C[j];
			}
		} else {
			int n = 1 << (32 - __builtin_clz(len));
			Vfft a(n), b(n);

			rep(i, 0, sz(C)) a[i] = C[i];
			rep(i, 0, sz(r.C)) b[i] = r.C[i];

			initFFT(n);
			fft<1>(a); fft<1>(b);
			rep(i, 0, sz(a)) a[i] = a[i]*b[i];
			fft<-1>(a);

			rep(i, 0, len) ret.C[i] = a[i];
		}

		ret.reduce();
		return ret;
	}

	Poly operator+(const Poly& r) const {
		Poly l = *this; l += r; return l;
	}
	Poly operator-(const Poly& r) const {
		Poly l = *this; l -= r; return l;
	}
	Poly& operator*=(const Poly& r) {
		return *this = *this * r;
	}

	// Derivate polynomial; time: O(n)
	void derivate() {
		rep(i, 1, sz(C)) C[i-1] = C[i]*i;
		C.pop_back();
	}

	// Integrate polynomial; time: O(n)
	void integrate() {
		C.pb(0);
		rep(i, 1, sz(C)) C[i] = C[i-1]/i;
		C[0] = 0;
	}
};
