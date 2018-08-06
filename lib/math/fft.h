#pragma once
#include "../template.h"
#include "modular.h"

// In-place Fast Fourier Transform
// over Z_p or complex; time: O(n lg n)
// DFT is in bit-reversed order!
// Default uncommented version is Z_p

// MOD = 15*(1<<27)+1          // Set this MOD!
constexpr ll ROOT = 440564289; // order = 1<<27

// using Vfft = vector<complex<double>>;
using Vfft = vector<Zp>;
Vfft bases;

void initFFT(int n) { // n must be power of 2
	bases.resize(n+1, 1);
//auto b = exp(complex<double>(0, 2*M_PI/n));
	auto b = Zp(ROOT).pow((1<<27) / n);
	rep(i, 1, n+1) bases[i] = b * bases[i-1];
}

template<int dir> // 1 for DFT, -1 for inverse
void fft(Vfft& buf) {
	int n = sz(buf), bits = 31-__builtin_clz(n);
	int i = (dir > 0 ? 0 : bits-1);

	for (; i >= 0 && i < bits; i += dir) {
		int shift = 1 << (bits-i-1);

		rep(j, 0, 1 << i) rep(k, 0, shift) {
			int a = (j << (bits-i)) | k;
			int b = a | shift;
			auto v1 = buf[a], v2 = buf[b];
			auto base = bases[(dir*(k<<i)) & (n-1)];

			if (dir > 0) {
				buf[b] = (v1 - v2) * base;
			} else {
				v2 = v2*base;
				buf[b] = v1 - v2;
			}
			buf[a] = v1 + v2;
		}
	}

	if (dir < 0) each(x, buf) x = x/n;
}

// Compute convolution of a and b; O(n lg n)
// Set a and b size appropriately
Vfft convolve(Vfft a, Vfft b) {
	fft<1>(a); fft<1>(b);
	rep(i, 0, sz(a)) a[i] = a[i]*b[i];
	fft<-1>(a);
	return a;
}
