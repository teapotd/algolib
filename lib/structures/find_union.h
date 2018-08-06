#pragma once
#include "../template.h"

// Disjoint set data structure; space: O(n)
// Operations work in amortized O(alfa(n))
struct FAU {
	Vi G;
	FAU(int n = 0) { init(n); }
	void init(int n) { G.assign(n, -1); }

	// Get size of set containing i
	int size(int i) { return -G[find(i)]; }

	// Find representative of set containing i
	int find(int i) {
		return G[i] < 0 ? i : G[i] = find(G[i]);
	}

	// Union sets containing i and j
	void join(int i, int j) {
		i = find(i); j = find(j);
		if (i == j) return;
		if (G[i] > G[j]) swap(i, j);
		G[i] += G[j]; G[j] = i;
	}
};
