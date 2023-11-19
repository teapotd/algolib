#include "../../../src/math/berlekamp_massey.h"
#include "../base_test.hpp"

void deterministic() {
}

void fuzz() {
	rep(t, 0, 4'000) {
		vector<ll> A(200);
		each(k, A) k = randInt(0, 200);

		auto C = massey(A);
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

		assert(A == B);
	}
}

void benchmark() {
}
