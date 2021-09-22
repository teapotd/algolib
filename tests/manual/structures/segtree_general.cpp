#define TREE_PLUS 1
#include "../../../src/structures/segtree_general.h"
#include "../testing.h"

struct NaivePlus {
	using T = int;
	vector<T> elems;

	struct Agg {
		T sum{0}, vMax{INT_MIN}, nMax{0};
	};

	NaivePlus(int n = 0, T def = 0) {
		elems.resize(n, def);
	}

	void update(int begin, int end, T val) {
		rep(i, begin, end) {
			elems[i] += val;
		}
	}

	Agg query(int begin, int end) {
		Agg ret;
		rep(i, begin, end) {
			ret.sum += elems[i];
			if (ret.vMax < elems[i]) ret.nMax = 1;
			else if (ret.vMax == elems[i]) ret.nMax++;
			ret.vMax = max(ret.vMax, elems[i]);
		}
		return ret;
	}
};

template<class Fast, class Naive>
void test(int n, int times) {
	Fast tree(n);
	Naive naive(n);

	rep(t, 0, times) {
		int b = r(0, n-1), e = r(0, n-1);
		if (b >= e) swap(b, e);
		e++;

		auto expected = naive.query(b, e);
		auto got = tree.query(b, e);

		// deb(b, e);
		// deb(got.sum, got.vMax, got.nMax);
		// deb(expected.sum, expected.vMax, expected.nMax);

		assert(got.sum == expected.sum);
		assert(got.vMax == expected.vMax);
		assert(got.nMax == expected.nMax);

		b = r(0, n-1), e = r(0, n-1);
		if (b >= e) swap(b, e);
		e++;

		int val = r(-5, 5);
		// deb(b, e, val);
		naive.update(b, e, val);
		tree.update(b, e, val);
	}
}

template<class Fast, class Naive>
void test() {
	for (int n = 1; n < 1000; n += 10) {
		test<Fast, Naive>(n, 8000);
	}
}

int main() {
	test<SegTree, NaivePlus>();
	return 0;
}
