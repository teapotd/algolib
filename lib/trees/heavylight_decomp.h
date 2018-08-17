#pragma once
#include "../template.h"
#include "../structures/segment_tree_point.h"

// Heavy-Light Decomposition of tree
// with example segment tree; space O(n)

struct Vert {
	Vi edges;
	int parent, size, depth, chain, chainPos;
};

struct Chain {
	Vi verts;
	SegmentTree tree;
};

vector<Vert> G;
vector<Chain> chains;

// Decompose tree rooted at i into chains; O(n)
void hld(int i, int parent = -1, int d = 0) {
	int h = -1;
	G[i].parent = parent;
	G[i].depth = d;
	G[i].size = 1;

	each(e, G[i].edges) if (e != parent) {
		hld(e, i, d+1);
		G[i].size += G[e].size;
		if (h < 0 || G[h].size < G[e].size) h = e;
	}

	if (h < 0) {
		h = sz(chains);
		chains.emplace_back();
	} else {
		h = G[h].chain;
	}
	chains[h].verts.pb(i);
	G[i].chain = h;

	if (parent < 0) {
		each(p, chains) {
			reverse(all(p.verts));
			rep(j, 0, sz(p.verts))
				G[p.verts[j]].chainPos = j;

			p.tree.init(sz(p.verts), 0);
		}
	}
}

// Level Ancestor Query; time: O(lg n)
int laq(int i, int level) {
	while (true) {
		int k = G[i].chainPos - (G[i].depth-level);
		if (k >= 0)
			return chains[G[i].chain].verts[k];
		i = G[chains[G[i].chain].verts[0]].parent;
	}
}

// Lowest Common Ancestor; time: O(lg n)
int lca(int a, int b) {
	while (G[a].chain != G[b].chain) {
		auto& ha = G[chains[G[a].chain].verts[0]];
		auto& hb = G[chains[G[b].chain].verts[0]];
		if (ha.depth > hb.depth)
			a = ha.parent;
		else
			b = hb.parent;
	}
	return G[a].depth < G[b].depth ? a : b;
}

// Call func(chain, begin, end) on each path
// segment; time: O(lg n * time of func)
template<class T>
void iterPath(int a, int b, T func) {
	while (G[a].chain != G[b].chain) {
		auto& ha = G[chains[G[a].chain].verts[0]];
		auto& hb = G[chains[G[b].chain].verts[0]];

		if (ha.depth > hb.depth) {
			func(ha.chain, 0, G[a].chainPos+1);
			a = ha.parent;
		} else {
			func(hb.chain, 0, G[b].chainPos+1);
			b = hb.parent;
		}
	}

	int x = G[a].chainPos+1, y = G[b].chainPos+1;
	func(G[a].chain, min(x, y), max(x, y));
}

// Query path between a and b; O(lg^2 n)
SegmentTree::T queryPath(int i, int j) {
	auto ret = SegmentTree::ID;
	iterPath(i, j, [&](int chain, int b, int e) {
			ret = SegmentTree::merge(ret,
					chains[chain].tree.query(b, e));
	});
	return ret;
}
