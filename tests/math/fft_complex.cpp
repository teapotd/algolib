#include "../../lib/math/fft_complex.h"
#include "../testing.h"

vector<cmpl> naiveConvolve(vector<cmpl>& A, vector<cmpl>& B) {
	int len = sz(A) + sz(B) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	A.resize(n); B.resize(n);

	vector<cmpl> ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) {
		auto& x = ret[(i+j)&(n-1)];
		x = x + A[i]*B[j];
	}

	ret.resize(len);
	return ret;
}

void randData(vector<cmpl>& data) {
	each(d, data) d = complex<double>(r(-1000, 1000), r(-1000, 1000));
}

int main() {
	cerr << fixed << setprecision(10);

	// int n = 1<<20;
	// vector<cmpl> d1(n), d2(n);
	// randData(d1);
	// randData(d2);
	// vector<cmpl> x1 = convolve(d1, d2);

	for (int i = 0; i < 14; i++) {
		int n = 1 << i;

		vector<cmpl> d1(n), d2(n);
		randData(d1);
		randData(d2);

		vector<cmpl> x1 = d1;
		convolve(x1, d2);
		vector<cmpl> x2 = naiveConvolve(d1, d2);

		double diff = 0;
		rep(j, 0, n) {
			auto d = abs(x1[i]-x2[i]);
			diff = max(max(diff, real(d)), imag(d));
		}

		deb(i, n, diff);
	}
	return 0;
}
