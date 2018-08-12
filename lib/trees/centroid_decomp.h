#pragma once
#include "../template.h"

// Centroid decomposition; space: O(n lg n)
// UNTESTED

struct Vert {
	// cE = edges to children centroids
	// cLinks[i] = vertex index in
	//             i-th centroid from root
	// cSubtree = vertices in centroid subtree
	// cDists = distances to vertices in subtree
	// cParent = parent centroid
	// cDepth = depth in centroid tree
	// cSize = subtree size
	Vi E, cE, cLinks, cSubtree, cDists;
	int cParent{-2}, cDepth{-1}, cSize{-1};
};

vector<Vert> G;

// Check if DFS should go to edge e if it came
// to current node from p. Also ignores
// vertices with cParent != -2 (established
// centroids). Used by functions below
bool can(int e, int p) {
	return e != p && G[e].cParent == -2;
}

// Computes subtree sizes
int computeSize(int i, int p) {
	int& s = G[i].cSize = 1;
	each(e, G[i].E) if (can(e, p))
		s += computeSize(e, i);
	return s;
}

// Finds centroid
int getCentroid(int i) {
	int p = -1, size = computeSize(i, -1);
	bool ok = true;
	while (ok) {
		ok = false;
		each(e, G[i].E) if (can(e, p)) {
			if (G[e].cSize > size/2) {
				p = i; i = e; ok = true;
				break;
			}
		}
	}
	G[i].cSize = size;
	return i;
}

// Calculate centroid subtree data
void dfsLayer(int i, int p, int centr, int d) {
	G[i].cLinks.pb(sz(G[centr].cSubtree));
	G[centr].cSubtree.pb(i);
	G[centr].cDists.pb(d);

	each(e, G[i].E) if (can(e, p))
		dfsLayer(e, i, centr, d+1);
}

// Perform centroid decomposition of tree
// containing `i`; time: O(n lg n)
// Returns root centroid.
int centroidDecomp(int i, int depth = 0) {
	i = getCentroid(i);
	G[i].cParent = -1;
	G[i].cDepth = depth;
	dfsLayer(i, -1, i, 0);

	each(e, G[i].E) if (can(e, -1)) {
		G[i].cE.pb(centroidDecomp(e, depth+1));
		G[G[i].cE.back()].cParent = i;
	}
	return i;
}
