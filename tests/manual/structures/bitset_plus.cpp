#include "../../../src/structures/bitset_plus.h"
#include "../testing.h"

int main() {
	constexpr int n = 10;

	vector<bool> A(n), B(n);
	rep(i, 0, n) {
		A[i] = r(0, 1);
		B[i] = r(0, 1);
	}

	deb(A);
	deb(B);
	A ^= B;
	deb(A);
	return 0;
}
