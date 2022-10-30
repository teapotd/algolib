#define TREE_PLUS 1
#include "../../../src/structures/segtree_persist.h"
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
	map<int, Naive> naive;
	vi versions;

	naive[0] = Naive(n);
	versions.pb(0);

	rep(t, 0, times) {
		int ver = versions[r(0, sz(versions)-1)];

		int b = r(0, n-1), e = r(0, n-1);
		if (b >= e) swap(b, e);
		e++;

		auto expected = naive[ver].query(b, e);
		auto got = tree.query(ver, b, e);

		// deb(ver, b, e);
		// deb(got.sum, got.vMax, got.nMax);
		// deb(expected.sum, expected.vMax, expected.nMax);

		assert(got.sum == expected.sum);
		assert(got.vMax == expected.vMax);
		assert(got.nMax == expected.nMax);

		if (r(0, 1)) {
			int newVer = tree.fork(ver);
			assert(naive.count(newVer) == 0);
			naive[newVer] = naive[ver];
			versions.pb(newVer);
			ver = newVer;
		}

		b = r(0, n-1), e = r(0, n-1);
		if (b >= e) swap(b, e);
		e++;

		int val = r(-5, 5);
		// deb(ver, b, e, val);
		naive[ver].update(b, e, val);
		tree.update(ver, b, e, val);
	}
}

template<class Fast, class Naive>
void test() {
	for (int n = 1; n < 1000; n += 10) {
		test<Fast, Naive>(n, 2000);
	}
}

int main() {
	test<SegTree, NaivePlus>();
	return 0;
}
