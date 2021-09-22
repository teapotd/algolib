#include "../../../src/util/inversion_vector.h"
#include "../../../src/template.h"
#include "../testing.h"

Vi naive(const Vi& perm) {
	Vi ans;
	rep(i, 0, sz(perm)) {
		int x = 0;
		rep(j, 0, i) {
			if (perm[j] > perm[i]) x++;
		}
		ans.pb(x);
	}
	return ans;
}

void test(const Vi& perm) {
	auto vec1 = encodeInversions(perm);
	auto vec2 = naive(perm);

	rep(i, 0, sz(perm)) {
		if (vec1[i] != vec2[i]) {
			deb(perm, vec1, vec2);
			exit(0);
		}
	}
}

int main() {
	rep(i, 0, 10000) {
		int n = r(0, 1000);
		Vi perm(n);
		rep(j, 0, n) perm[j] = r(0, n-1);
		test(perm);
	}
	return 0;
}
