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

cmpl operator*=(cmpl& a,cmpl b) {return a=a*b;}

// Compute DFT over complex numbers; O(n lg n)
// Input size must be power of 2!
void fft(vector<cmpl>& a) {
	static vector<cmpl> w(2, 1);
	int n = sz(a);

	for (int k = sz(w); k < n; k *= 2) {
		w.resize(n);
		rep(i,0,k) w[k+i] = exp(cmpl(0, M_PI*i/k));
	}

	Vi rev(n);
	rep(i,0,n) rev[i] = (rev[i/2] | i%2*n) / 2;
	rep(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);

	for (int k = 1; k < n; k *= 2) {
		for (int i=0; i < n; i += k*2) rep(j,0,k) {
			auto d = a[i+j+k] * w[j+k];
			a[i+j+k] = a[i+j] - d;
			a[i+j] += d;
		}
	}
}

// Convolve complex-valued a and b,
// store result in a; time: O(n lg n), 3x FFT
void convolve(vector<cmpl>& a, vector<cmpl> b){
	int len = sz(a) + sz(b) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	a.resize(n); b.resize(n);
	fft(a); fft(b);
	rep(i, 0, n) a[i] *= b[i] / dbl(n);
	reverse(a.begin()+1, a.end());
	fft(a);
	a.resize(len);
}

// Convolve real-valued a and b, return result
// time: O(n lg n), 2x FFT
vector<dbl> convolve(vector<dbl>& a,
                     vector<dbl>& b) {
	int len = sz(a) + sz(b) - 1;
	int n = 1 << (32 - __builtin_clz(len));

	vector<cmpl> in(n), out(n);
	rep(i, 0, sz(a)) in[i].real(a[i]);
	rep(i, 0, sz(b)) in[i].imag(b[i]);

	fft(in);
	each(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i&(n-1)]-conj(in[i]);
	fft(out);

	vector<dbl> ret(len);
	rep(i, 0, len) ret[i] = imag(out[i]) / (n*4);
	return ret;
}
