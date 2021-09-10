#include "../../src/graphs/boski_matching.h"
#include "../testing.h"

int main() {
	int n = 500000;
	Matching M(n);

	rep(i, 0, n) {
		Vi vec(r(1, 5));
		each(k, vec) k = r(0, n-1);
		M.add(vec);
	}

	return 0;
}
