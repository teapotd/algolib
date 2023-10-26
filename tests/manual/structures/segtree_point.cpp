#include "../../../src/structures/segtree_point.h"
#include "../testing.h"

constexpr int LEN = 100;

vector<int> elems(LEN);
SegTree tree;

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

bool checkLowerBound(int val) {
	int expected = -1, cur = INT_MIN;
	rep(i, 0, LEN+1) {
		if (cur >= val) {
			expected = i;
			break;
		}
		if (i < LEN) {
			cur = max(cur, elems[i]);
		}
	}

	int got = tree.lowerBound(val);
	return expected == got;
}

int main() {
	tree = {LEN, 0};

	rep(i, 0, 10000) {
		int pos = r(0, LEN-1);
		int val = r(-10, 10);

		elems[pos] = val;
		tree.set(pos, val);

		rep(b, 0, LEN) rep(e, 0, LEN+1) {
			assert(checkQuery(b, e));
		}
		rep(v, -1, tree.V[1]+5) {
			assert(checkLowerBound(v));
		}
	}
	
	return 0;
}
