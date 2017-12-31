#pragma once
#include "../template.h"

using Vfft = vector<complex<double>>;
Vfft bases;

void initFFT(int n) {
	bases.resize(n+1, 1);
	bases[1] = exp(complex<double>(0, 2*M_PI/n));
	rep(i,2,n+1) bases[i] = bases[i-1]*bases[1];
}

void fft(Vfft& buf, bool inv) {
	int n = sz(buf), k = 0;
	while ((1 << k) < n) k++;

	rep(i, 0, n) { // Bit reversal
		int j = 0;
		for (int a = 1; a < n; a <<= 1, j <<= 1)
			if (a & i) j |= 1;
		j >>= 1;
		if (i < j) swap(buf[i], buf[j]);
	}

	for (int s = 1; s < n; s <<= 1) {
		k--;
		for (int i=0; i<n; i += 2*s) rep(j, 0, s) {
			auto u = buf[i+j], v = buf[i+j+s];
			if (inv) v *= bases[n - (j<<k)];
			else     v *= bases[(j<<k)];
			buf[i+j] = u+v; buf[i+j+s] = u-v;
		}
	}
}
