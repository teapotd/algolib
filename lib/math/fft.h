#pragma once
#include "../template.h"

using Vfft = vector<complex<double>>;
Vfft bases;

void initFFT(int n) {
	bases.resize(n+1, 1);
	bases[1] = exp(complex<double>(0, 2*M_PI/n));
	rep(i,2,n+1) bases[i] = bases[i-1]*bases[1];
}

template<int dir>
void fft(Vfft& buf) {
	int n = sz(buf), bits = 31-__builtin_clz(n);
	int i = (dir > 0 ? 0 : bits-1);

	for (; i >= 0 && i < bits; i += dir) {
		int shift = 1 << (bits-i-1);

		rep(j, 0, 1 << i) rep(k, 0, shift) {
			int a = (j << (bits-i)) | k;
			int b = a | shift;
			auto v1 = buf[a], v2 = buf[b];
			auto base = bases[(dir*(1<<i)) & (n-1)];

			if (dir > 0) {
				buf[b] = (v1 - v2) * base;
			} else {
				v2 *= base;
				buf[b] = (v1 - v2);
			}
			buf[a] = v1 + v2;
		}
	}

	if (dir < 0) each(x, buf) x /= n;
}
