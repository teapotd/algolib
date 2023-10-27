#include "point_config_mock.h"
#include "../../../src/segtree/point_fixed.h"
#include "../testing.hpp"

struct VerifiedSegTree {
	int n;
	SegTree tree;
	Naive naive;

	VerifiedSegTree() : n(0) {}
	VerifiedSegTree(int n_) : n(n_), tree(n), naive(n) {}
	VerifiedSegTree(int n_, T def) : n(n_), tree(n, def), naive(n, def) {}

	void set(int j) {
		T val = randInt(0, 1e9);
		tree.set(j, val);
		naive.set(j, val);
	}

	void checkQuery(int b, int e) {
		auto got = tree.query(b, e);
		auto exp = naive.query(b, e);
		if (got != exp) {
			deb(n, b, e, got, exp);
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
			return agg.size >= k;
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
	tree.checkQueries(-5, 5, -5, 5);
	tree.checkLowerBounds();

	tree = {0};
	tree.checkQueries(-5, 5, -5, 5);
	tree.checkLowerBounds();

	tree = {1};
	tree.checkQueries(-5, 5, -5, 5);
	tree.set(0);
	tree.checkQueries(-5, 5, -5, 5);
	tree.checkLowerBounds();

	rep(n, 2, 100) {
		tree = {n};
		tree.checkLowerBounds();
	}
}

void fuzz() {
	int n = randInt(1, 2000);
	VerifiedSegTree tree(n);
	tree.checkLowerBounds();

	for (int op = 0; op < 200000; op++) {
		if (randBool()) {
			int j = randInt(0, n-1);
			tree.set(j);
		} else if (randBool()) {
			int b = randInt(-10, n+10);
			int e = randInt(-10, n+10);
			tree.checkQuery(b, e);
		} else {
			int k = randInt(0, n+1);
			tree.checkLowerBound(k);
		}
	}
}

void benchmark() {
}
