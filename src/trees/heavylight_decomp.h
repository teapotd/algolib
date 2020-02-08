#pragma once
#include "../template.h"
#include "../structures/seg_tree_point.h"

// Heavy-Light Decomposition of tree
// with subtree query support; space: O(n)
struct HLD {
	// Subtree of v = [pos[v]; pos[v]+size[v])
	// Chain with v = [chBegin[v]; chEnd[v])
	Vi par;     // Vertex parent
	Vi size;    // Vertex subtree size
	Vi depth;   // Vertex distance to root
	Vi pos;     // Vertex position in "HLD" order
	Vi chBegin; // Begin of chain with vertex
	Vi chEnd;   // End of chain with vertex
	Vi order;   // "HLD" preorder of vertices
	SegmentTree tree; // Verts are in HLD order

	HLD() {}

	// Initialize structure for tree G
	// and given root; time: O(n lg n)
	// MODIFIES ORDER OF EDGES IN G!
	HLD(vector<Vi>& G, int root)
			: par(sz(G)), size(sz(G)),
			  depth(sz(G)), pos(sz(G)),
			  chBegin(sz(G)), chEnd(sz(G)) {
		dfs(G, root, -1);
		decomp(G, root, -1, 0);
		tree = {sz(order)};
	}

	void dfs(vector<Vi>& G, int v, int p) {
		par[v] = p;
		size[v] = 1;
		depth[v] = p < 0 ? 0 : depth[p]+1;

		int& fs = G[v][0];
		if (fs == p) swap(fs, G[v].back());

		each(e, G[v]) if (e != p) {
			dfs(G, e, v);
			size[v] += size[e];
			if (size[e] > size[fs]) swap(e, fs);
		}
	}

	void decomp(vector<Vi>& G,
	            int v, int p, int chb) {
		pos[v] = sz(order);
		chBegin[v] = chb;
		chEnd[v] = pos[v]+1;
		order.pb(v);

		each(e, G[v]) if (e != p) {
			if (e == G[v][0]) {
				decomp(G, e, v, chb);
				chEnd[v] = chEnd[e];
			} else {
				decomp(G, e, v, sz(order));
			}
		}
	}

	// Get root of chain containing v
	int chRoot(int v) {return order[chBegin[v]];}

	// Level Ancestor Query; time: O(lg n)
	int laq(int v, int level) {
		while (true) {
			int k = pos[v] - depth[v] + level;
			if (k >= chBegin[v]) return order[k];
			v = par[chRoot(v)];
		}
	}

	// Lowest Common Ancestor; time: O(lg n)
	int lca(int a, int b) {
		while (chBegin[a] != chBegin[b]) {
			int ha = chRoot(a), hb = chRoot(b);
			if (depth[ha] > depth[hb]) a = par[ha];
			else b = par[hb];
		}
		return depth[a] < depth[b] ? a : b;
	}

	// Call func(chBegin, chEnd) on each path
	// segment; time: O(lg n * time of func)
	template<class T>
	void iterPath(int a, int b, T func) {
		while (chBegin[a] != chBegin[b]) {
			int ha = chRoot(a), hb = chRoot(b);
			if (depth[ha] > depth[hb]) {
				func(chBegin[a], pos[a]+1);
				a = par[ha];
			} else {
				func(chBegin[b], pos[b]+1);
				b = par[hb];
			}
		}

		if (pos[a] > pos[b]) swap(a, b);
		// Remove +1 from pos[a]+1 for vertices
		// queries (with +1 -> edges).
		func(pos[a]+1, pos[b]+1);
	}

	// Query path between a and b; O(lg^2 n)
	SegmentTree::T queryPath(int a, int b) {
		auto ret = SegmentTree::ID;
		iterPath(a, b, [&](int i, int j) {
			ret = SegmentTree::merge(ret,
					tree.query(i, j));
		});
		return ret;
	}

	// Query subtree of v; time: O(lg n)
	SegmentTree::T querySubtree(int v) {
		return tree.query(pos[v], pos[v]+size[v]);
	}
};
