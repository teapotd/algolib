#pragma once
#include "../template.h"

// Link/cut tree; space: O(n)
// Represents forest of (un)rooted trees
struct LinkCutTree {
	struct Node {
		int E[2] = {-1, -1}, par{-1}, prev{-1};
		bool flip{0};
	};

	vector<Node> G;

	// Initialize structure for n vertices; O(n)
	LinkCutTree(int n = 0) { init(n); }
	void init(int n) { G.assign(n, {}); }

	void auxLink(int par, int i, int child) {
		G[par].E[i] = child;
		if (child >= 0) G[child].par = par;
	}

	void push(int x) {
		if (x >= 0 && G[x].flip) {
			G[x].flip = 0;
			swap(G[x].E[0], G[x].E[1]);
			each(e, G[x].E) if (e>=0) G[e].flip ^= 1;
		}
	}

	void rot(int p, int i) {
		int x = G[p].E[i], g = G[x].par = G[p].par;
		if (g >= 0) G[g].E[G[g].E[1] == p] = x;
		auxLink(p, i, G[x].E[!i]);
		auxLink(x, !i, p);
		swap(G[x].prev, G[p].prev);
	}

	void splay(int x) {
		while (G[x].par >= 0) {
			int p = G[x].par, g = G[p].par;
			push(g); push(p); push(x);
			bool f = (G[p].E[1] == x);

			if (g >= 0) {
				if (G[g].E[f] == p) { // zig-zig
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

	void access(int x) {
		while (true) {
			splay(x);
			int p = G[x].prev;
			if (p < 0) break;

			G[x].prev = -1;
			splay(p);

			int r = G[p].E[1];
			if (r >= 0) swap(G[r].par, G[r].prev);
			auxLink(p, 1, x);
		}
	}

	void makeRoot(int x) {
		access(x);
		int& l = G[x].E[0];
		if (l >= 0) {
			swap(G[l].par, G[l].prev);
			G[l].flip ^= 1;
			l = -1;
		}
	}

	// Find representative of tree containing x
	int find(int x) { // time: amortized O(lg n)
		access(x);
		while (G[x].E[0] >= 0) push(x = G[x].E[0]);
		splay(x);
		return x;
	}

	// Add edge x-y; time: amortized O(lg n)
	void link(int x, int y) {
		makeRoot(x); G[x].prev = y;
	}

	// Remove edge x-y; time: amortized O(lg n)
	void cut(int x, int y) {
		makeRoot(x); access(y);
		G[x].par = G[y].E[0] = -1;
	}
};
