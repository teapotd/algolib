#include "../../../src/math/fwht.h"
#include "../base_test.hpp"

vector<ll> naiveBitConv(vector<ll> A, vector<ll> B) {
	vector<ll> ret(sz(A));
	rep(i, 0, sz(A)) rep(j, 0, sz(A)) {
		ret[i FWHT_OP j] += A[i] * B[j];
	}
	return ret;
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 5'000) {
		int p = i%11;
		vector<ll> A(1<<p), B(1<<p);
		each(k, A) k = randInt(-1e5, 1e5);
		each(k, B) k = randInt(-1e5, 1e5);

		auto expected = naiveBitConv(A, B);
		bitConv(A, B);
		assert(A == expected);
	}
}

void benchmark() {
}
