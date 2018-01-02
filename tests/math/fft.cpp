#include "../../lib/math/fft.h"
#include "../testing.h"

Vfft naiveConvolve(Vfft& A, Vfft& B) {
	int n = sz(A);
	assert(n == sz(B));

	Vfft ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) ret[(i+j)&(n-1)] += A[i] * B[j];
	return ret;
}

Vfft fftConvolve(Vfft A, Vfft B) {
	int n = sz(A);
	assert(n == sz(B));

	fft<1>(A);
	fft<1>(B);
	rep(i, 0, n) A[i] *= B[i];
	fft<-1>(A);
	return A;
}

void randCmpl(Vfft& data) {
	each(d, data) d = complex<double>(r(-1000, 1000), r(-1000, 1000));
}

int main() {
	cerr << fixed << setprecision(10);

	for (int i = 0; i < 15; i++) {
		int n = 1 << i;
		initFFT(n);

		Vfft d1(n), d2(n);
		randCmpl(d1);
		randCmpl(d2);

		Vfft x1 = fftConvolve(d1, d2);
		Vfft x2 = naiveConvolve(d1, d2);

		double diff = 0;
		rep(j, 0, n) {
			auto d = abs(x1[i]-x2[i]);
			diff = max(max(diff, real(d)), imag(d));
		}

		deb(i, n, diff);
	}
	return 0;
}
