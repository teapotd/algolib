#include "../../src/structures/segment_tree_beats.h"
#include "../testing.h"

struct Checker {
	using T = SegmentTree::T;
	vector<T> elems;
	SegmentTree tree;

	Checker(int n) : elems(n), tree(n) {}

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
		// deb(begin, end, ret, tree.getSum(begin, end));
		assert(ret == tree.getSum(begin, end));
	}

	void getMax(int begin, int end) {
		T ret = -INF;
		rep(i, begin, end) ret = max(ret, elems[i]);
		assert(ret == tree.getMax(begin, end));
	}
};

void timeTest() {
	constexpr int N = 1e6;
	constexpr int Q = 1e6;
	SegmentTree tree(N);

	rep(j, 0, Q) {
		int b = r(0, N), e = r(0, N);
		if (b > e) swap(b, e);

		switch (r(1, 4)) {
			case 1:
				tree.add(b, e, r(-1e5, 1e5));
				break;
			case 2:
				tree.setMin(b, e, r(-1e9, 1e9));
				break;
			case 3:
				tree.getMax(b, e);
				break;
			case 4:
				tree.getSum(b, e);
				break;
		}
	}
}

int main() {
	//timeTest();
	//return 0;

	rep(i, 0, 1000) {
		int n = r(1, 50);
		Checker check(n);

		rep(j, 0, 10000) {
			int b = r(0, n), e = r(0, n);
			if (b > e) swap(b, e);

			switch (r(1, 4)) {
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
