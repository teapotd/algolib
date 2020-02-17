#pragma once
#include "../template.h"

// Helper for offline centroid decomposition
// Usage: CentroidDecomp(G);
// Constructor calls method `process`
// for each centroid subtree.
struct CentroidDecomp {
	vector<Vi>& G; // Reference to target graph
	vector<bool> on; // Is vertex enabled?
	Vi size; // Used internally

	// Run centroid decomposition for graph g
	CentroidDecomp(vector<Vi>& g)
			: G(g), on(sz(g), 1), size(sz(g)) {
		decomp(0);
	}

	// Compute subtree sizes for subtree rooted
	// at v, ignoring p and disabled vertices
	void computeSize(int v, int p) {
		size[v] = 1;
		each(e, G[v]) if (e != p && on[e])
			computeSize(e, v), size[v] += size[e];
	}

	void decomp(int v) {
		computeSize(v, -1);
		int p = -1, s = size[v];
	loop:
		each(e, G[v]) {
			if (e != p && on[e] && size[e] > s/2) {
				p = v; v = e; goto loop;
			}
		}
		process(v);
		on[v] = 0;
		each(e, G[v]) if (on[e]) decomp(e);
	}

	// Process current centroid subtree:
	// - v is centroid
	// - boundary vertices have on[x] = 0
	// Formally: Let H be subgraph induced
	// on vertices such that on[v] = 1.
	// Then current centroid subtree is
	// connected component of H that contains v
	// and v is its centroid.
	void process(int v) {
		// Do your stuff here...
	}
};
