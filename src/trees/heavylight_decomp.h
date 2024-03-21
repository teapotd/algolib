#pragma once
#include "../template.h"
#include "../segtree/point_fixed.h"

// Heavy-Light Decomposition of tree
// with subtree query support; space: O(n)
struct HLD {
	// G[v] = children of v (no parents!)
	// G[v][0] = heavy child of v
	// par[v] = parent of vertex v
	// size[v] = size of subtree rooted at v
	// depth[v] = distance from root to v
	// pos[v] = index of v in "HLD preorder"
	// head[v] = first vertex of chain with v
	// len[v] = length of chain starting at v
	//          (0 if v is not head of chain)
	// order[i] = i-th vertex in "HLD preorder"
	vector<vi> G;
	vi par, size, depth, pos, head, len, order;
	SegTree tree; // Vertices are in HLD order

	HLD() {}

	// Initialize structure for tree G
	// and given root v; time: O(n lg n)
	HLD(vector<vi> H, int v)
			: G(move(H)), par(sz(G), -1),
			  size(sz(G), 1), depth(sz(G)),
			  pos(sz(G)), head(sz(G)), len(sz(G)) {
		dfs(v);
		go(v, v);
		tree = {sz(order)};
	}

	void dfs(int v) {
		erase(G[v], par[v]);
		each(e, G[v]) {
			depth[e] = depth[par[e] = v] + 1;
			dfs(e);
			size[v] += size[e];
			if (size[e] > size[G[v][0]])
				swap(G[v][0], e);
		}
	}

	void go(int v, int h) {
		pos[v] = sz(order);
		len[head[v] = h]++;
		order.pb(v);
		each(e, G[v]) go(e, G[v][0] == e ? h : e);
	}

	// Level Ancestor Query; time: O(lg n)
	int laq(int v, int level) {
		for (;; v = par[v]) {
			int k = level - depth[v = head[v]];
			if (k >= 0) return order[pos[v]+k];
		}
	}

	// Lowest Common Ancestor; time: O(lg n)
	int lca(int a, int b) {
		for (;;) {
			int ha = head[a], hb = head[b];
			if (ha == hb)
				return depth[a] < depth[b] ? a : b;
			if (depth[ha] > depth[hb]) a = par[ha];
			else b = par[hb];
		}
	}

	// Call func(begin, end, isAscending)
	// for each path segment in order
	// from a to b; time: O(lg n * time of func)
	// func can be called on empty intervals!
	void iterPath(int a, int b, auto func) {
		for (static vector<pii> tmp;;) {
			int ha = head[a], hb = head[b];
			if (ha == hb) {
				bool f = (pos[a] > pos[b]);
				if (f) swap(a, b);
				// Remove +1 from pos[a]+1 for vertex
				// queries (with +1 -> edges).
				func(pos[a]+1, pos[b]+1, !f);
				reverse(all(tmp));
				each(e, tmp) func(e.x, e.y, 0);
				return tmp.clear();
			}
			if (depth[ha] > depth[hb]) {
				func(pos[ha], pos[a]+1, 1);
				a = par[ha];
			} else {
				tmp.pb({pos[hb], pos[b]+1});
				b = par[hb];
			}
		}
	}

	// Query path between a and b; O(lg^2 n)
	SegTree::T queryPath(int a, int b) {
		auto ret = tree.ID;
		iterPath(a, b, [&](int i, int j, bool) {
			ret = tree.f(ret, tree.query(i, j));
		});
		return ret;
	}

	// Query subtree of v; time: O(lg n)
	SegTree::T querySubtree(int v) {
		return tree.query(pos[v], pos[v]+size[v]);
	}
};
