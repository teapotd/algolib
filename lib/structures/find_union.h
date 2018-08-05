#pragma once
#include "../template.h"

struct FAU {
	Vi G;
	FAU(int n = 0) { init(n); }
	void init(int n) { G.assign(n, -1); }
	int size(int i) { return -G[find(i)]; }

	int find(int i) {
		return G[i] < 0 ? i : G[i] = find(G[i]);
	}

	void join(int i, int j) {
		i = find(i); j = find(j);
		if (i == j) return;
		if (G[i] > G[j]) swap(i, j);
		G[i] += G[j]; G[j] = i;
	}
};
