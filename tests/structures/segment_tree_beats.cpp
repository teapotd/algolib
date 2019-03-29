#include "../../lib/structures/segment_tree_beats.h"
#include "../testing.h"

struct Checker {
	using T = SegmentTree::T;
	vector<T> elems;
	SegmentTree tree;

	Checker(int n) {
		elems.resize(n);
		tree.init(n);
	}

	void setMin(int begin, int end, T x) {
		rep(i, begin, end) elems[i] = min(elems[i], x);
		tree.setMin(begin, end, x);
	}

	void add(int begin, int end, T x) {
		rep(i, begin, end) elems[i] += x;
		tree.add(begin, end, x);
	}

	void sum(int begin, int end) {
		T ret = 0;
		rep(i, begin, end) ret += elems[i];
		deb(begin, end, ret, tree.sum(begin, end));
		assert(ret == tree.sum(begin, end));
	}

	void getMax(int begin, int end) {
		T ret = -INF;
		rep(i, begin, end) ret = max(ret, elems[i]);
		assert(ret == tree.getMax(begin, end));
	}
};

int main() {
	rep(i, 0, 100) {
		int n = r(1, 5);
		Checker check(n);

		rep(j, 0, 10000) {
			int b = r(0, n), e = r(0, n);
			if (b > e) swap(b, e);

			switch (r(1, 5)) {
				case 1:
					check.setMin(b, e, r(-1e9, 1e9));
					break;
				case 2:
					check.add(b, e, r(-1e5, 1e5));
					break;
				case 3:
					check.getMax(b, e);
					break;
				case 4:
					check.sum(b, e);
					break;
			}
		}
	}
	return 0;
}
