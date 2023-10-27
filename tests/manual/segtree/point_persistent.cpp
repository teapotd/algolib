#include "../../../src/segtree/point_persistent.h"
#include "../testing.h"

constexpr int LEN = 100;

map<int, vector<int>> elems;
SegTree tree;

bool checkQuery(int ver, int begin, int end) {
	int node = tree.query(ver, begin, end);
	int great = INT_MIN;
	auto& vec = elems[ver];
	rep(i, begin, end) great = max(great, vec[i]);

	if (node != great) {
		deb(node, great);
		return false;
	}
	return true;
}

bool checkLowerBound(int ver, int val) {
	auto& vec = elems[ver];
	int expected = -1, cur = INT_MIN;
	rep(i, 0, LEN+1) {
		if (cur >= val) {
			expected = i;
			break;
		}
		if (i < LEN) {
			cur = max(cur, vec[i]);
		}
	}

	int got = tree.lowerBound(ver, val);
	return expected == got;
}

int main() {
	tree = {LEN, 0};
	elems[0].resize(LEN);

	vi versions = {0};

	rep(i, 0, 10000) {
		int ver = versions[r(0, sz(versions)-1)];
		int pos = r(0, LEN-1);
		int val = r(-10, 10);

		elems[ver][pos] = val;
		tree.set(ver, pos, val);

		rep(b, 0, LEN) rep(e, 0, LEN+1) {
			assert(checkQuery(ver, b, e));
		}
		rep(v, -1, tree.agg[ver]+5) {
			assert(checkLowerBound(ver, v));
		}
	}
	
	return 0;
}
