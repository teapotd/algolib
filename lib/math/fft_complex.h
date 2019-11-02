#pragma once
#include "../template.h"

using dbl = double;
using cmpl = complex<dbl>;

// Default std::complex multiplication is slow.
// You can use this to achieve small speedup.
cmpl operator*(cmpl a, cmpl b) {
	dbl ax = real(a), ay = imag(a);
	dbl bx = real(b), by = imag(b);
	return {ax*bx-ay*by, ax*by+ay*bx};
}

// Compute DFT over complex numbers; O(n lg n)
// DFT is in bit-reversed order!
// Input size must be power of 2!
template<bool inv> void fft(vector<cmpl>& a) {
	static vector<cmpl> w(2, 1);
	int n = sz(a);

	for (int k = sz(w); k < n; k *= 2) {
		w.resize(n);
		rep(i,0,k) w[k+i] = exp(cmpl(0, M_PI*i/k));
	}

	for (int t=1, s=n/2; t < n; t *= 2, s /= 2) {
		int k = (inv ? t : s);
		for (int i=0; i < n; i += k*2) rep(j,0,k) {
			auto &c = a[i+j], d = a[i+j+k], e=w[j+k];
			a[i+j+k] =
				(inv ? c - (d = d*conj(e)) : (c-d)*e);
			c += d;
		}
	}

	if (inv) each(k, a) k /= n;
}

// Convolve a and b, store result in a;
// time: O(n lg n)
void convolve(vector<cmpl>& a, vector<cmpl> b){
	int len = sz(a) + sz(b) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	a.resize(n); b.resize(n);
	fft<0>(a); fft<0>(b);
	rep(i, 0, n) a[i] *= b[i];
	fft<1>(a);
	a.resize(len);
}
