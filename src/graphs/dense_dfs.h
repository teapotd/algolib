#pragma once
#include "../template.h"
#include "../math/bit_matrix.h"

// DFS over bit-packed adjacency matrix
// G = NxN adjacency matrix of graph
//     G(i,j) <=> (i,j) is edge
// V = 1xN matrix containing unvisited vertices
//     V(0,i) <=> i-th vertex is not visited
// Total DFS time: O(n^2/64)
struct DenseDFS {
	BitMatrix G, V; // space: O(n^2/64)

	// Initialize structure for n vertices
	DenseDFS(int n = 0) : G(n, n), V(1, n) {
		reset();
	}

	// Mark all vertices as unvisited
	void reset() { each(x, V.M) x = -1; }

	// Get/set visited flag for i-th vertex
	void setvisited(int i) { V.set(0, i, 0); }
	bool isvisited(int i)  { return !V(0, i); }

	// DFS step: func is called on each unvisited
	// neighbour of i. You need to manually call
	// setvisited(child) to mark it visited
	// or this function will call the callback
	// with the same vertex again.
	template<class T>
	void step(int i, T func) {
		ull* E = G.row(i);
		for (int w = 0; w < G.stride;) {
			ull x = E[w] & V.row(0)[w];
			if (x) func((w<<6) | __builtin_ctzll(x));
			else   w++;
		}
	}
};
