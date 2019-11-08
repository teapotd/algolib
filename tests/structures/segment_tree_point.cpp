#include "../../src/structures/segment_tree_point.h"
#include "../testing.h"

constexpr int LEN = 100;

vector<int> elems(LEN);
SegmentTree tree;

void debugPrint() {
	deb(elems);
	deb(tree.V);
}

bool checkQuery(int begin, int end) {
	int node = tree.query(begin, end);
	int great = INT_MIN;
	rep(i, begin, end) great = max(great, elems[i]);

	if (node != great) {
		deb(node, great);
		debugPrint();
		return false;
	}
	return true;
}

int main() {
	tree = {LEN, 0};

	rep(i, 0, 10000) {
		int pos = r(0, LEN-1);
		int val = r(-10, 10);

		elems[pos] = val;
		tree.set(pos, val);

		rep(b, 0, LEN) rep(e, 0, LEN+1) {
			if (!checkQuery(b, e)) return 1;
		}
	}
	
	return 0;
}
