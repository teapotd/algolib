#pragma once

struct VerifiedSegTree {
	int n;
	SegTree tree;
	Naive naive;

	VerifiedSegTree() : n(0) {}
	VerifiedSegTree(int n_) : n(n_), tree(n), naive(n) {}

	void update(int b, int e) {
		auto val = sampleUpdate();
		tree.update(b, e, val);
		naive.update(b, e, val);
	}

	void checkQuery(int b, int e) {
		auto got = tree.query(b, e);
		auto exp = naive.query(b, e);
		assert(got == exp);
	}
};

void deterministic() {
}

void fuzz() {
	int n = randInt(1, 100);
	VerifiedSegTree tree(n);
	for (int op = 0; op < 50000; op++) {
		int b = randInt(0, n);
		int e = randInt(0, n);
		if (b > e) swap(b, e);
		if (randBool()) {
			tree.update(b, e);
		} else {
			tree.checkQuery(b, e);
		}
	}
}

void benchmark() {
}
