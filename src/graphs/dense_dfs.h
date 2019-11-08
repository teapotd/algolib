#pragma once
#include "../template.h"
#include "../math/bit_matrix.h"

// DFS over adjacency matrix; time: O(n^2/64)
// G = graph, V = not visited vertices masks
// UNTESTED
struct DenseDFS {
	BitMatrix G, V; // space: O(n^2/64)

	DenseDFS(int n = 0) : G(n, n), V(1, n) {
		reset();
	}

	void reset() { each(x, V.M) x = -1; }
	void setVisited(int i) { V.set(0, i, 0); }
	bool isVisited(int i)  { return !V(0, i); }

	// DFS step: func is called on each unvisited
	// neighbour of i. You need to manually call
	// setVisited(child) to mark it visited.
	template<class T> // Single step: O(n/64)
	void step(int i, T func) {
		ull* E = G.row(i);
		for (int w = 0; w < G.stride;) {
			ull x = E[w] & V.row(0)[w];
			if (x) func((w<<6) | __builtin_ctzll(x));
			else   w++;
		}
	}
};
