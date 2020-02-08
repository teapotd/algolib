#pragma once
#include "../template.h"

constexpr int INF = 1e9;

// Link/cut tree; space: O(n)
// Represents forest of (un)rooted trees.
struct LinkCutTree {
	vector<array<int, 2>> child;
	Vi par, prev, flip, size;

	// Initialize structure for n vertices; O(n)
	// At first there's no edges.
	LinkCutTree(int n = 0)
			: child(n, {-1, -1}), par(n, -1),
			  prev(n, -1), flip(n, -1), size(n, 1) {}

	void push(int x) {
		if (x >= 0 && flip[x]) {
			flip[x] = 0;
			swap(child[x][0], child[x][1]);
			each(e, child[x]) if (e>=0) flip[e] ^= 1;
		} // + any other lazy path operations
	}

	void update(int x) {
		if (x >= 0) {
			size[x] = 1;
			each(e, child[x]) if (e >= 0)
				size[x] += size[e];
		} // + any other path aggregates
	}

	void auxLink(int p, int i, int ch) {
		child[p][i] = ch;
		if (ch >= 0) par[ch] = p;
		update(p);
	}

	void rot(int p, int i) {
		int x = child[p][i], g = par[x] = par[p];
		if (g >= 0) child[g][child[g][1] == p] = x;
		auxLink(p, i, child[x][!i]);
		auxLink(x, !i, p);
		swap(prev[x], prev[p]);
		update(g);
	}

	void splay(int x) {
		while (par[x] >= 0) {
			int p = par[x], g = par[p];
			push(g); push(p); push(x);
			bool f = (child[p][1] == x);
			if (g >= 0) {
				if (child[g][f] == p) { // zig-zig
					rot(g, f); rot(p, f);
				} else { // zig-zag
					rot(p, f); rot(g, !f);
				}
			} else { // zig
				rot(p, f);
			}
		}
		push(x);
	}

	// After this operation x becomes the end
	// of preferred path starting in root;
	void access(int x) { // amortized O(lg n)
		while (true) {
			splay(x);
			int p = prev[x];
			if (p < 0) break;

			prev[x] = -1;
			splay(p);

			int r = child[p][1];
			if (r >= 0) swap(par[r], prev[r]);
			auxLink(p, 1, x);
		}
	}

	// Make x root of its tree; amortized O(lg n)
	void makeRoot(int x) {
		access(x);
		int& l = child[x][0];
		if (l >= 0) {
			swap(par[l], prev[l]);
			flip[l] ^= 1;
			update(l);
			l = -1;
			update(x);
		}
	}

	// Find root of tree containing x
	int find(int x) { // time: amortized O(lg n)
		access(x);
		while (child[x][0] >= 0)
			push(x = child[x][0]);
		splay(x);
		return x;
	}

	// Add edge x-y; time: amortized O(lg n)
	// Root of tree containing y becomes
	// root of new tree.
	void link(int x, int y) {
		makeRoot(x); prev[x] = y;
	}

	// Remove edge x-y; time: amortized O(lg n)
	// x and y become roots of new trees!
	void cut(int x, int y) {
		makeRoot(x); access(y);
		par[x] = child[y][0] = -1;
		update(y);
	}

	// Get distance between x and y,
	// returns INF if x and y there's no path.
	// This operation makes x root of the tree!
	int dist(int x, int y) { // amortized O(lg n)
		makeRoot(x);
		if (find(y) != x) return INF;
		access(y);
		int t = child[y][0];
		return t >= 0 ? size[t] : 0;
	}
};
