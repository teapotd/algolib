#pragma once
#include "../template.h"

using cmpl = complex<double>;
using Vfft = vector<cmpl>;

// Compute DFT over complex numbers; O(n lg n)
// DFT is in bit-reversed order!
// Input size must be power of 2!
template<int dir> // 1 for DFT, -1 for inverse
void fft(Vfft& buf) {
	assert(__builtin_popcount(sz(buf)) == 1);
	int n = sz(buf), bits = 31-__builtin_clz(n);
	int i = (dir > 0 ? 0 : bits-1);

	Vfft bases = {1};
	auto c = exp(cmpl(0, 2*M_PI/n));
	rep(k, 0, n) bases.pb(bases.back()*c);

	for (; i >= 0 && i < bits; i += dir) {
		int shift = 1 << (bits-i-1);
		rep(j, 0, 1 << i) rep(k, 0, shift) {
			int a = (j << (bits-i)) | k, b = a|shift;
			auto v1 = buf[a], v2 = buf[b];
			auto base = bases[(dir*(k<<i)) & (n-1)];
			if (dir > 0) {
				buf[b] = (v1 - v2) * base;
			} else {
				v2 *= base;
				buf[b] = v1 - v2;
			}
			buf[a] = v1 + v2;
		}
	}

	if (dir < 0) each(x, buf) x /= n;
}

// Convolve a and b, store result in a;
// time: O(n lg n)
void convolve(Vfft& a, Vfft b) {
	int len = sz(a) + sz(b) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	a.resize(n); b.resize(n);
	fft<1>(a); fft<1>(b);
	rep(i, 0, n) a[i] *= b[i];
	fft<-1>(a);
	a.resize(len);
}
