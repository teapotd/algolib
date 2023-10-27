#define TREE_BEATS 1
#include "../../../src/segtree/general_fixed.h"
#include "../testing.h"

struct Checker {
	using T = int;
	vector<T> elems;
	SegTree tree;

	Checker(int n) : elems(n), tree(n) {}

	void setMin(int begin, int end, T x) {
		rep(i, begin, end) elems[i] = min(elems[i], x);
		tree.update(begin, end, {0, x});
	}

	void add(int begin, int end, T x) {
		rep(i, begin, end) elems[i] += x;
		tree.update(begin, end, {x, INT_MAX});
	}

	void sum(int begin, int end) {
		T expected = 0;
		rep(i, begin, end) expected += elems[i];
		T got = tree.query(begin, end).sum;
		// deb(expected, got);
		assert(expected == got);
	}

	void getMax(int begin, int end) {
		T expected = INT_MIN;
		rep(i, begin, end) expected = max(expected, elems[i]);
		T got = tree.query(begin, end).vMax;
		// deb(expected, got);
		assert(expected == got);
	}
};

void timeTest() {
	constexpr int N = 1e6;
	constexpr int Q = 1e6;
	SegTree tree(N);

	rep(j, 0, Q) {
		int b = r(0, N), e = r(0, N);
		if (b > e) swap(b, e);

		switch (r(1, 3)) {
			case 1:
				tree.update(b, e, {r(-1e3, 1e3), INT_MAX});
				break;
			case 2:
				tree.update(b, e, {0, r(-1e6, 1e6)});
				break;
			case 3:
				tree.query(b, e);
				break;
		}
	}
}

int main() {
	// timeTest();
	// return 0;

	rep(i, 0, 1000) {
		int n = r(1, 50);
		Checker check(n);

		rep(j, 0, 10000) {
			int b = r(0, n), e = r(0, n);
			if (b > e) swap(b, e);

			switch (r(1, 4)) {
				case 1:
					check.setMin(b, e, r(-1e6, 1e6));
					break;
				case 2:
					check.add(b, e, r(-1e3, 1e3));
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
