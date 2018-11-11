#pragma once
#include "../template.h"
#include "../structures/segment_tree_point.h"

// Heavy-Light Decomposition of tree
// with subtree query support; space: O(n)

struct Vert {
	// par = parent, size = subtree size
	// depth = distance to root
	// pos = position in hldOrder
	// chBegin = begin of chain in hldOrder
	//           (closest to root)
	// chEnd = end of chain in hldOrder,
	//         EXCLUSIVE (furthest from root)
	Vi E; // Neighbours
	int par, size, depth, pos, chBegin, chEnd;
};

vector<Vert> G; // Graph
Vi hldOrder; // "HLD" preorder of vertices
SegmentTree hldTree; // Verts are in hldOrder

// Subtree of v = [G[v].pos;G[v].pos+G[v].size)
// Chain with v = [G[v].chBegin;G[v].chEnd)

// Get root of chain containg v
int chRoot(int v) {
	return hldOrder[G[v].chBegin];
}

void dfsSize(int i, int p, int d) {
	G[i].par = p;
	G[i].size = 1;
	G[i].depth = d;

	auto& fs = G[i].E[0];
	if (fs == p) swap(fs, G[i].E.back());

	each(e, G[i].E) if (e != p) {
		dfsSize(e, i, d+1);
		G[i].size += G[e].size;
		if (G[e].size > G[fs].size) swap(e, fs);
	}
}

void dfsHld(int i, int p, int chb) {
	G[i].pos = sz(hldOrder);
	G[i].chBegin = chb;
	G[i].chEnd = G[i].pos+1;
	hldOrder.pb(i);

	each(e, G[i].E) if (e != p) {
		if (e == G[i].E[0]) {
			dfsHld(e, i, chb);
			G[i].chEnd = G[e].chEnd;
		} else {
			dfsHld(e, i, sz(hldOrder));
		}
	}
}

// Initialize decomposition; time: O(n)
void hld(int v) {
	hldOrder.clear();
	dfsSize(v, -1, 0);
	dfsHld(v, -1, 0);
	hldTree.init(sz(hldOrder), 0);
}

// Level Ancestor Query; time: O(lg n)
int laq(int i, int level) {
	while (true) {
		int k = G[i].pos - G[i].depth + level;
		if (k >= G[i].chBegin) return hldOrder[k];
		i = G[chRoot(i)].par;
	}
}

// Lowest Common Ancestor; time: O(lg n)
int lca(int a, int b) {
	while (G[a].chBegin != G[b].chBegin) {
		auto& ha = G[chRoot(a)];
		auto& hb = G[chRoot(b)];
		if (ha.depth > hb.depth) a = ha.par;
		else b = hb.par;
	}
	return G[a].depth < G[b].depth ? a : b;
}

// Call func(chBegin, chEnd) on each path
// segment; time: O(lg n * time of func)
template<class T>
void iterPath(int a, int b, T func) {
	while (G[a].chBegin != G[b].chBegin) {
		auto& ha = G[chRoot(a)];
		auto& hb = G[chRoot(b)];

		if (ha.depth > hb.depth) {
			func(G[a].chBegin, G[a].pos+1);
			a = ha.par;
		} else {
			func(G[b].chBegin, G[b].pos+1);
			b = hb.par;
		}
	}

	if (G[a].pos > G[b].pos) swap(a, b);
	// Remove +1 from G[a].pos+1 for vertices
	// queries (with +1 -> edges).
	func(G[a].pos+1, G[b].pos+1);
}

// Query path between a and b; time: O(lg^2 n)
SegmentTree::T queryPath(int a, int b) {
	auto ret = SegmentTree::ID;
	iterPath(a, b, [&](int i, int j) {
		ret = SegmentTree::merge(ret,
			hldTree.query(i, j));
	});
	return ret;
}

// Query subtree of v; time: O(lg n)
SegmentTree::T querySubtree(int v) {
	return hldTree.query(G[v].pos,
	                     G[v].pos+G[v].size);
}
