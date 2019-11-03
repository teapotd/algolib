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
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastFourierTransform.h
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

// Convolve real-valued a and b, returns result
// time: O(n lg n), 2x FFT
// Rounding to integers is safe as long as
// (max_coeff^2)*n*log_2(n) < 9*10^14
// (in practice 10^16 or higher).
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastFourierTransform.h
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

constexpr ll MOD = 1e9+7;

// High precision convolution of integer-valued
// a and b mod MOD; time: O(n lg n), 4x FFT
// Input is expected to be in range [0;MOD).
// Rounding is safe if MOD*n*log_2(n) < 9*10^14
// (in practice 10^16 or higher).
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastFourierTransformMod.h
vector<ll> convolve(vector<ll>& a, vector<ll>& b) {
	vector<ll> ret(sz(a) + sz(b) - 1);
	int n = 1 << (32 - __builtin_clz(sz(ret)));
	ll cut = ll(sqrt(MOD))+1;

	vector<cmpl> c(n), d(n), g(n), f(n);

	rep(i, 0, sz(a))
		c[i] = {dbl(a[i]/cut), dbl(a[i]%cut)};
	rep(i, 0, sz(b))
		d[i] = {dbl(b[i]/cut), dbl(b[i]%cut)};

	fft(c); fft(d);

	rep(i, 0, n) {
		int j = -i & (n-1);
		f[j] = (c[i]+conj(c[j])) * d[i] / (n*2.0);
		g[j] =
			(c[i]-conj(c[j])) * d[i] / cmpl(0, n*2);
	}

	fft(f); fft(g);

	rep(i, 0, sz(ret)) {
		ll t = llround(real(f[i])) % MOD * cut;
		t += llround(imag(f[i]));
		t = (t + llround(real(g[i]))) % MOD * cut;
		t = (t + llround(imag(g[i]))) % MOD;
		ret[i] = (t < 0 ? t+MOD : t);
	}

	return ret;
}
