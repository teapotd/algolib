#pragma once
#include "../template.h"
#include "../math/bit_matrix.h"

struct DenseDFS {
	BitMatrix G, V;

	DenseDFS(int n) : G(n,n), V(1,n) { reset(); }
	void reset() { each(x, V.M) x = -1; }

	void setVisited(int i) { V.set(0, i, 0); }
	bool isVisited(int i)  { return V(0, i); }

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
