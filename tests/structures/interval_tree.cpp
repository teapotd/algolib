#include "../../lib/structures/interval_tree.h"
#include "../testing.h"

constexpr int LEN = 300;

int main() {
	vector<int> elems(LEN);
	IntervalTree tree(LEN);

	for (int i = 0; i < 1000000; i++) {
		int k = r(-1000, 1000);
		int a = r(0, LEN), b = r(0, LEN);
		if (a > b) swap(a, b);

		for (int i = a; i < b; i++) elems[i] += k;
		tree.modify(a, b, k);

		a = r(0, LEN), b = r(0, LEN);
		if (a > b) swap(a, b);

		int elem = INT_MIN;
		for (int i = a; i < b; i++) elem = max(elem, elems[i]);

		int count = 0;
		for (int i = a; i < b; i++) if (elems[i] == elem) count++;
		
		int tmp = 0;
		// printf("%d %d\n", tree.query(a, b), elem);
		assert(tree.queryCount(a, b, tmp) == elem);
		// printf("%d %d\n", tmp, count);
		assert(tmp == count);
	}

	return 0;
}
