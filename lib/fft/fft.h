#include "../template.h"

Vcmpl bases;

void initFft(int siz) {
	bases.resize(siz+1);
	rep(i, 0, siz+1) bases[i] = exp(cmpl(0, 2*M_PI*i/siz));
}

template<bool inv>
void fft(Vcmpl::IT in, Vcmpl::IT out, int siz, int s = 1) {
	if (siz == 1) { *out = *in; return; }

	fft<inv>(in,   out,       siz*2, s*2);
	fft<inv>(in+s, out+siz/2, siz*2, s*2);

	rep(i, 0, siz/2) {
		auto t = out[i], m = bases[(inv ? i : siz-i)*s];
		out[i]       = t + out[i+siz/2]*m;
		out[i+siz/2] = t - out[i+siz/2]*m;
	}
}
