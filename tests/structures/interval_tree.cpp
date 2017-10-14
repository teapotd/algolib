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

		int tmp = 0;
		for (int i = a; i < b; i++) tmp += elems[i];
		
		// printf("%d %d %d %d\n", a, b, tree.query(a, b), tmp);
		assert(tree.query(a, b) == tmp);
	}

	return 0;
}
