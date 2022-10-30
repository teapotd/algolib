#pragma once
#include "../template.h"

// Disjoint set data structure; space: O(n)
// Operations work in amortized O(alfa(n))
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/UnionFind.h
struct FAU {
	vi G;
	FAU(int n = 0) : G(n, -1) {}

	// Get size of set containing i
	int size(int i) { return -G[find(i)]; }

	// Find representative of set containing i
	int find(int i) {
		return G[i] < 0 ? i : G[i] = find(G[i]);
	}

	// Union sets containing i and j
	bool join(int i, int j) {
		i = find(i); j = find(j);
		if (i == j) return 0;
		if (G[i] > G[j]) swap(i, j);
		G[i] += G[j]; G[j] = i;
		return 1;
	}
};
