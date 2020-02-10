#include "../../src/math/berlekamp_massey.h"
#include "../testing.h"

void check(vector<ll>& A) {
	vector<ll> C = massey(A);
	assert(sz(C)*2 <= sz(A)+1);

	vector<ll> B(sz(A));

	rep(i, 0, sz(A)) {
		if (i < sz(C)) {
			B[i] = A[i];
		} else {
			rep(j, 0, sz(C)) {
				B[i] = (B[i] + B[i-j-1]*C[j]) % MOD;
			}
		}
	}

	cerr << '\n';
	deb(A);
	deb(B);
	deb(C);
	assert(A == B);
}

int main() {
	rep(i, 0, 10) {
		vector<ll> data(20);
		each(k, data) k = r(0, 20);
		check(data);
	}
	return 0;
}
