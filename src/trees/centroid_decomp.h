#pragma once
#include "../template.h"

// Centroid decomposition; space: O(n lg n)
struct CentroidTree {
	// child[v] = children of v in centroid tree
	// par[v] = parent of v in centroid tree
	//          (-1 for root)
	// depth[v] = depth of v in centroid tree
	//            (0 for root)
	// ind[v][i] = index of vertex v in i-th
	//             centroid subtree from root
	// size[v] = size of centroid subtree of v
	// subtree[v] = list of vertices
	//              in centroid subtree of v
	// dists[v] = distances from v to vertices
	//            in its centroid subtree
	//            (in the order of subtree[v])
	// neigh[v] = neighbours of v
	//            in its centroid subtree
	// dir[v][i] = index of centroid neighbour
	//             that is first vertex on path
	//             from centroid v to i-th vertex
	//             of centroid subtree
	//             (-1 for centroid)
	vector<vi> child, ind, dists, subtree,
	           neigh, dir;
	vi par, depth, size;
	int root; // Root centroid

	CentroidTree() {}

	CentroidTree(vector<vi>& G)
			: child(sz(G)), ind(sz(G)), dists(sz(G)),
			  subtree(sz(G)), neigh(sz(G)),
			  dir(sz(G)), par(sz(G), -2),
			  depth(sz(G)), size(sz(G)) {
		root = decomp(G, 0, 0);
	}

	void dfs(vector<vi>& G, int v, int p) {
		size[v] = 1;
		each(e, G[v]) if (e != p && par[e] == -2)
			dfs(G, e, v), size[v] += size[e];
	}

	void layer(vector<vi>& G, int v,
	           int p, int c, int d) {
		ind[v].pb(sz(subtree[c]));
		subtree[c].pb(v);
		dists[c].pb(d);
		dir[c].pb(sz(neigh[c])-1);
		each(e, G[v]) if (e != p && par[e] == -2) {
			if (v == c) neigh[c].pb(e);
			layer(G, e, v, c, d+1);
		}
	}

	int decomp(vector<vi>& G, int v, int d) {
		dfs(G, v, -1);
		int p = -1, s = size[v];
	loop:
		each(e, G[v]) {
			if (e != p && par[e] == -2 &&
			    size[e] > s/2) {
				p = v; v = e; goto loop;
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
