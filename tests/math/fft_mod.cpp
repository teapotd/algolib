#include "../../lib/math/fft_mod.h"
#include "../testing.h"

vector<ll> naiveConvolve(vector<ll>& A, vector<ll>& B) {
	int len = sz(A) + sz(B) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	A.resize(n); B.resize(n);

	vector<ll> ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) {
		auto& x = ret[(i+j)&(n-1)];
		x = (x + A[i]*B[j]) % MOD;
	}

	ret.resize(len);
	each(x, ret) if (x < 0) x += MOD;
	return ret;
}

void randData(vector<ll>& data) {
	each(d, data) d = r(0, 1000);
}

int main() {
	cerr << fixed << setprecision(10);

	// int n = 1<<20;
	// Vfft d1(n), d2(n);
	// randData(d1);
	// randData(d2);
	// Vfft x1 = convolve(d1, d2);

	for (int i = 0; i < 14; i++) {
		int n = 1 << i;

		vector<ll> d1(n), d2(n);
		randData(d1);
		randData(d2);

		vector<ll> x1 = d1;
		convolve(x1, d2);
		vector<ll> x2 = naiveConvolve(d1, d2);

		ll diff = 0;
		rep(j, 0, n) {
			auto d = abs(x1[i]-x2[i]);
			diff = max(diff, d);
		}

		deb(i, n, diff);
	}
	return 0;
}
