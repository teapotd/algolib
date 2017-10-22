#pragma once
#include "../template.h"

// Recursive Cooley-Tukey FFT over complex numbers
// Time complexity: O(n lg n)

vector<cmpl> bases;

void initFft(int size) {
	bases.resize(size+1);
	rep(i, 0, size+1) bases[i] = exp(cmpl(0, 2*M_PI*i/size));
}

template<bool inv>
void fft(vector<cmpl>::IT in, vector<cmpl>::IT out, int size, int step = 1) {
	if (size == 1) { *out = *in; return; }

	fft<inv>(in,      out,        size/2, step*2);
	fft<inv>(in+step, out+size/2, size/2, step*2);

	rep(i, 0, size/2) {
		auto t = out[i], m = bases[(inv ? i : size-i)*step];
		out[i]        = t + out[i+size/2]*m;
		out[i+size/2] = t - out[i+size/2]*m;
	}
}

template<bool inv>
vector<cmpl> fft(vector<cmpl>& in) {
	vector<cmpl> out(sz(in));
	fft<inv>(in.begin(), out.begin(), sz(in));
	if (inv) each(x, out) x /= sz(in);
	return out;
}
