#pragma once
#include "../template.h"

// Centroid decomposition; space: O(n lg n)
// UNTESTED
struct CentroidTree {
	// child[v] = children of v in centroid tree
	// ind[v][i] = index of vertex v in
	//             i-th centroid from root
	// subtree[v] = vertices in centroid subtree
	// dists[v] = distances from v to vertices
	//            in centroid subtree
	// par[v] = parent of v in centroid tree
	// depth[v] = depth of v in centroid tree
	// size[v] = size of centroid subtree of v
	vector<Vi> child, ind, dists, subtree;
	Vi par, depth, size;
	int root; // Root centroid

	CentroidTree() {}

	CentroidTree(vector<Vi>& G)
			: child(sz(G)), ind(sz(G)), dists(sz(G)),
			  subtree(sz(G)), par(sz(G), -2),
			  depth(sz(G)), size(sz(G)) {
		root = decomp(G, 0, 0);
	}

	int dfs(vector<Vi>& G, int v, int p) {
		size[v] = 1;
		each(e, G[v]) if (e != p && par[e] == -2)
			size[v] += dfs(G, e, v);
		return size[v];
	}

	void layer(vector<Vi>& G, int v,
	           int p, int c, int d) {
		ind[v].pb(sz(subtree[c]));
		subtree[c].pb(v);
		dists[c].pb(d);
		each(e, G[v]) if (e != p && par[e] == -2)
			layer(G, e, v, c, d+1);
	}

	int decomp(vector<Vi>& G, int v, int d) {
		int p = -1, s = dfs(G, v, -1);
		bool ok = 1;
		while (ok) {
			ok = 0;
			each(e, G[v]) {
				if (e != p && par[e] == -2 &&
						size[e] > s/2) {
					p = v; v = e; ok = 1;
					break;
				}
			}
		}

		par[v] = -1;
		size[v] = s;
		depth[v] = d;
		layer(G, v, -1, v, 0);

		each(e, G[v]) if (par[e] == -2) {
			int j = decomp(G, e, d+1);
			child[v].pb(j);
			par[j] = v;
		}
		return v;
	}
};
