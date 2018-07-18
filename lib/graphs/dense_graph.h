#pragma once
#include "../template.h"

using ull = uint64_t;
using Vull = vector<ull>;

struct DenseGraph {
	Vull M, marked;
	int n, stride;

	DenseGraph(int k) {
		n = k;
		stride = (k+63)>>6;
		M.resize(n*stride);
		marked.resize(stride, -1);
	}

	ull* edges(int i) { return &M[i*stride]; }
	void addEdge(int i, int j) {
		edges(i)[j>>6] |= 1ull << (j&63);
	}

	void visit(int i) {
		marked[i>>6] &= ~(1ull << (i&63));
	}

	bool isVisited(int i) {
		return ~marked[i>>6] & (1ull << (i&63));
	}

	template<class T>
	void dfsStep(int i, T func) {
		ull* E = edges(i);
		for (int w = 0; w < stride;) {
			ull x = E[w] & marked[w];
			if (x) func((w<<6) | __builtin_ctzll(x));
			else   w++;
		}
	}
};
