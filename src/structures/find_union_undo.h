#pragma once
#include "../template.h"

// Disjoint set data structure
// with rollback; space: O(n)
// Operations work in O(log(n)) time.
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/UnionFindRollback.h
struct RollbackFAU {
	Vi G;
	vector<Pii> his;

	RollbackFAU(int n = 0) : G(n, -1) {}

	// Get size of set containing i
	int size(int i) { return -G[find(i)]; }

	// Find representative of set containing i
	int find(int i) {
		return G[i] < 0 ? i : find(G[i]);
	}

	// Current time (for rollbacks)
	int time() { return sz(his); }

	// Rollback all operations after time `t`
	void rollback(int t) {
		for (int i = time(); t < i--;)
			G[his[i].x] = his[i].y;
		his.resize(t);
	}

	// Union sets containing i and j
	bool join(int i, int j) {
		i = find(i); j = find(j);
		if (i == j) return 0;
		if (G[i] > G[j]) swap(i, j);
		his.pb({i, G[i]});
		his.pb({j, G[j]});
		G[i] += G[j]; G[j] = i;
		return 1;
	}
};
