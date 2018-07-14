#include "../../lib/math/fft.h"
#include "../testing.h"

Vfft naiveConvolve(Vfft& A, Vfft& B) {
	int n = sz(A);
	assert(n == sz(B));

	Vfft ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) {
		auto& x = ret[(i+j)&(n-1)];
		x = x + A[i]*B[j];
	}
	return ret;
}

void randData(Vfft& data) {
	// each(d, data) d = complex<double>(r(-1000, 1000), r(-1000, 1000));
	each(d, data) d = r(0, 1000);
}

int main() {
	cerr << fixed << setprecision(10);

	// int n = 1<<20;
	// Vfft d1(n), d2(n);
	// randData(d1);
	// randData(d2);

	// initFFT(n);
	// Vfft x1 = convolve(d1, d2);

	for (int i = 0; i < 15; i++) {
		int n = 1 << i;
		initFFT(n);

		Vfft d1(n), d2(n);
		randData(d1);
		randData(d2);

		Vfft x1 = convolve(d1, d2);
		Vfft x2 = naiveConvolve(d1, d2);

		ll diff = 0;
		rep(j, 0, n) {
			auto d = abs(x1[i].x-x2[i].x);
			// diff = max(max(diff, real(d)), imag(d));
			diff = max(diff, d);
		}

		deb(i, n, diff);
	}
	return 0;
}
