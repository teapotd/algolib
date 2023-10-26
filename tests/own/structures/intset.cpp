#include "../../../src/structures/intset.h"
#include "../testing.hpp"

void deterministic() {
}

void fuzz() {
}

void benchmark() {
	constexpr int N = 1e7;
	IntSet<N> ds;

	vector<int> ord(N);
	iota(all(ord), 0);
	randShuffle(ord);

	// Warm-up
	for (int i : ord) {
		ds.add(i);
	}
	for (int i : ord) {
		ds.del(i);
	}

	measure("add N=1e7", 1, [&] {
		for (int i : ord) {
			ds.add(i);
		}
	});

	measure("del N=1e7", 1, [&] {
		for (int i : ord) {
			ds.del(i);
		}
	});

	measure("add+del N=1e7", 1, [&] {
		for (int i : ord) {
			ds.add(i);
			ds.del(i);
		}
	});

	for (int j = 0; j < 100; j++) {
		ds.add(ord[j]);
	}

	measure("next N=1e7", 1, [&] {
		for (int i : ord) {
			consume(ds.next(i));
		}
	});

	measure("prev N=1e7", 1, [&] {
		for (int i : ord) {
			consume(ds.next(i));
		}
	});

	consume(&ds);
}
