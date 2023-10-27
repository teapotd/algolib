#include "config_mock.hpp"
#include "../../../../src/segtree/general_persistent.h"
#include "../../testing.hpp"

struct VerifiedSegTree {
	int n;
	SegTree tree;
	map<int, Naive> naive;
	vi versions = {0};

	VerifiedSegTree() : n(0) {
		naive[0] = {};
	}

	VerifiedSegTree(int n_) : n(n_), tree(n) {
		naive[0] = {n};
	}

	int randVersion() {
		return randElement(versions);
	}

	int fork(int i) {
		assert(naive.count(i));
		int j = tree.fork(i);
		assert(!naive.count(j));
		naive[j] = naive[i];
		versions.pb(j);
		return j;
	}

	void update(int i, int b, int e) {
		assert(naive.count(i));
		T val = randInt(0, 1e9);
		tree.update(i, b, e, val);
		naive[i].update(b, e, val);
	}

	void checkQuery(int i, int b, int e) {
		assert(naive.count(i));
		auto got = tree.query(i, b, e).seq;
		auto exp = naive[i].query(b, e);
		if (got != exp) {
			deb(n, i, b, e);
			deb(got);
			deb(exp);
			assert(0);
		}
	}

	void checkQueries(int i, int b1, int b2, int e1, int e2) {
		rep(b, b1, b2+1) {
			rep(e, e1, e2+1) {
				checkQuery(i, b, e);
			}
		}
	}

	void checkLowerBound(int i, int k) {
		int got = tree.lowerBound(i, [&](auto agg) {
			return int(agg.seq.size()) >= k;
		});
		int exp = (k <= n ? max(k, 0) : -1);
		if (got != exp) {
			deb(n, i, k, got, exp);
			assert(0);
		}
	}

	void checkLowerBounds(int i) {
		rep(k, 0, n+2) {
			checkLowerBound(i, k);
		}
	}
};

void deterministic() {
	VerifiedSegTree tree;
	tree.checkQueries(0, 0, 5, -5, 0);
	int j = tree.fork(0);
	tree.update(j, 0, 0);
	tree.checkQueries(0, 0, 5, -5, 0);
	tree.checkQueries(j, 0, 5, -5, 0);
	tree.checkLowerBounds(0);

	tree = {0};
	tree.checkQueries(0, 0, 5, -5, 0);
	j = tree.fork(0);
	tree.update(j, 0, 0);
	tree.checkQueries(0, 0, 5, -5, 0);
	tree.checkQueries(j, 0, 5, -5, 0);
	tree.checkLowerBounds(0);

	tree = {1};
	tree.checkQueries(0, 0, 5, -5, 1);
	j = tree.fork(0);
	tree.update(j, 0, 1);
	tree.checkQueries(0, 0, 5, -5, 1);
	tree.checkQueries(j, 0, 5, -5, 1);
	tree.checkLowerBounds(0);

	rep(n, 2, 100) {
		tree = {n};
		tree.checkLowerBounds(0);
	}
}

void fuzz() {
	int n = randInt(1, 500);
	VerifiedSegTree tree(n);
	tree.checkLowerBounds(0);

	for (int op = 0; op < 50000; op++) {
		int ver = tree.randVersion();
		if (randBool()) {
			int b = randInt(0, n);
			int e = randInt(0, n);
			tree.update(ver, b, e);
		} else if (randBool()) {
			int b = randInt(0, n);
			int e = randInt(0, n);
			tree.checkQuery(ver, b, e);
		} else if (randBool()) {
			int k = randInt(0, n+1);
			tree.checkLowerBound(ver, k);
		} else {
			tree.fork(ver);
		}
	}
}

void benchmark() {
}
