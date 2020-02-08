#include "../../src/structures/seg_tree.h"
#include "../testing.h"

constexpr int LEN = 100;

vector<int> elems(LEN);
SegmentTree tree(LEN, 0);

void debugPrint() {
	deb(elems);
	// rep(i, 1, sz(tree.V)) {
	// 	cerr << i << ": " << tree.V[i] << endl;
	// }
	// cerr << endl;
}

bool checkQuery(int begin, int end) {
	auto node = tree.query(begin, end);
	int sum = 0, great = INT_MIN, nGreat = 0;

	rep(i, begin, end) {
		sum += elems[i];
		great = max(great, elems[i]);
	}

	rep(i, begin, end) nGreat += (elems[i] == great);

	if (node.sum != sum || node.great != great || node.nGreat != nGreat) {
		deb(begin, end);
		deb(node.sum, sum);
		deb(node.great, great);
		deb(node.nGreat, nGreat);
		debugPrint();
		return false;
	}

	return true;
}

int main() {
	rep(i, 0, 1000) {
		int begin = r(0, LEN-1);
		int end = r(0, LEN-1);
		int val = r(-10, 10);

		if (begin > end) swap(begin, end);
		if (begin == end) end++;

		rep(j, begin, end) elems[j] += val;               // +
		// rep(j, begin, end) elems[j] = max(elems[j], val); // max
		// rep(j, begin, end) elems[j] = val;                // =

		tree.modify(begin, end, val);

		rep(b, 0, LEN) rep(e, 0, LEN+1) {
			if (!checkQuery(b, e)) return 1;
		}
	}
	
	return 0;
}
