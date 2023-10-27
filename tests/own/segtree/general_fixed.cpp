#include "general_config_mock.h"
#include "../../../src/segtree/general_fixed.h"
#include "../testing.hpp"

struct VerifiedSegTree {
	int n;
	SegTree tree;
	Naive naive;

	VerifiedSegTree() : n(0) {}
	VerifiedSegTree(int n_) : n(n_), tree(n), naive(n) {}

	void update(int b, int e) {
		T val = randInt(0, 1e9);
		tree.update(b, e, val);
		naive.update(b, e, val);
	}

	void checkQuery(int b, int e) {
		auto got = tree.query(b, e).seq;
		auto exp = naive.query(b, e);
		if (got != exp) {
			deb(n, b, e);
			deb(got);
			deb(exp);
			assert(0);
		}
	}

	void checkQueries(int b1, int b2, int e1, int e2) {
		rep(b, b1, b2+1) {
			rep(e, e1, e2+1) {
				checkQuery(b, e);
			}
		}
	}

	void checkLowerBound(int k) {
		int got = tree.lowerBound([&](auto agg) {
			return int(agg.seq.size()) >= k;
		});
		int exp = (k <= n ? max(k, 0) : -1);
		if (got != exp) {
			deb(n, k, got, exp);
			assert(0);
		}
	}

	void checkLowerBounds() {
		rep(k, 0, n+2) {
			checkLowerBound(k);
		}
	}
};

void deterministic() {
	VerifiedSegTree tree;
	tree.checkQueries(0, 5, -5, 0);
	tree.update(0, 0);
	tree.checkQueries(0, 5, -5, 0);
	tree.checkLowerBounds();

	tree = {0};
	tree.checkQueries(0, 5, -5, 0);
	tree.update(0, 0);
	tree.checkQueries(0, 5, -5, 0);
	tree.checkLowerBounds();

	tree = {1};
	tree.checkQueries(0, 5, -5, 1);
	tree.update(0, 1);
	tree.checkQueries(0, 5, -5, 1);
	tree.checkLowerBounds();

	rep(n, 2, 100) {
		tree = {n};
		tree.checkLowerBounds();
	}
}

void fuzz() {
	int n = randInt(1, 500);
	VerifiedSegTree tree(n);
	tree.checkLowerBounds();

	for (int op = 0; op < 50000; op++) {
		if (randBool()) {
			int b = randInt(0, n);
			int e = randInt(0, n);
			tree.update(b, e);
		} else if (randBool()) {
			int b = randInt(0, n);
			int e = randInt(0, n);
			tree.checkQuery(b, e);
		} else {
			int k = randInt(0, n+1);
			tree.checkLowerBound(k);
		}
	}
}

void benchmark() {
}
