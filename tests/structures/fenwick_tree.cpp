#include "../../lib/structures/fenwick_tree.h"
#include "../testing.h"

int main() {
	int N = r(10, 100);

	Fenwick tree(N);
	vector<int> naive(N);

	rep(i, 0, N) {
		naive[i] = r(-1e4, 1e4);
		tree.modify(i, naive[i]);
	}

	int sum = 0;
	rep(i, 0, N) {
		assert(tree.query(i) == sum);
		sum += naive[i];
	}
	assert(tree.query(N) == sum);

	rep(i, 0, 100000000) {
		int pos = r(0, N);

		if (r(0, 1)) {
			if (pos >= N) {
				pos = N-1;
			}

			int old = naive[pos];
			naive[pos] = r(-1e4, 1e4);
			tree.modify(pos, naive[pos]-old);
		} else {
			sum = tree.query(pos);
			for (int j = 0; j < pos; j++) {
				sum -= naive[j];
			}
			assert(sum == 0);
		}
	}
	return 0;
}
