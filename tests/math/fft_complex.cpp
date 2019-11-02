#include "../../lib/math/fft_complex.h"
#include "../testing.h"

vector<dbl> naiveConvolve(vector<dbl>& A, vector<dbl>& B) {
	int len = sz(A) + sz(B) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	A.resize(n); B.resize(n);

	vector<dbl> ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) {
		auto& x = ret[(i+j)&(n-1)];
		x = x + A[i]*B[j];
	}

	ret.resize(len);
	return ret;
}

void randData(vector<dbl>& data) {
	each(d, data) d = dbl(r(-1000, 1000));
}

int main() {
	cerr << fixed << setprecision(10);

	// int n = 1<<20;
	// vector<dbl> d1(n), d2(n);
	// randData(d1);
	// randData(d2);
	// d1 = convolve(d1, d2);

	// cout << d1[123] << endl;

	for (int i = 0; i < 14; i++) {
		int n = 1 << i;

		vector<dbl> d1(n), d2(n);
		randData(d1);
		randData(d2);

		vector<dbl> x1 = convolve(d1, d2);
		vector<dbl> x2 = naiveConvolve(d1, d2);

		assert(sz(x1) == sz(x2));

		double diff = 0;
		rep(j, 0, sz(x1)) {
			auto d = abs(x1[i]-x2[i]);
			diff = max(max(diff, real(d)), imag(d));
		}

		deb(i, n, diff);
	}
	return 0;
}
