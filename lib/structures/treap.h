#pragma once
#include "../template.h"

// "Set" of implicit keyed treaps; space: O(n)
// Treaps are distinguished by roots indices
// Put any additional data in Node struct.
struct Treap {
	struct Node {
		int E[2] = {-1, -1}, weight{rand()};
		int size{1}, par{-1};
		bool flip{false}; // Is interval reversed?
	};

	vector<Node> G;

	// Initialize structure for n nodes; O(n)
	// Each node is separate treap,
	// use join() to construct sequence.
	Treap(int n = 0) { init(n); }
	void init(int n) { G.clear(); G.resize(n); }

	int size(int x) { // Returns subtree size
		return (x >= 0 ? G[x].size : 0);
	}

	void push(int x) { // Propagates down stuff
		if (x >= 0 && G[x].flip) {
			G[x].flip = 0;
			swap(G[x].E[0], G[x].E[1]);
			each(e, G[x].E) if (e>=0) G[e].flip ^= 1;
		} // + any other lazy operations
	}

	void update(int x) { // Updates aggregates
		if (x >= 0) {
			int& s = G[x].size = 1;
			G[x].par = -1;
			each(e, G[x].E) if (e >= 0) {
				s += G[e].size;
				G[e].par = x;
			}
		} // + any other aggregates
	}

	// Split treap x by index i into l and r
	// average time: O(lg n)
	void split(int x, int& l, int& r, int i) {
		push(x); l = r = -1;
		if (x < 0) return;
		int key = size(G[x].E[0]);
		if (i <= key) {
			split(G[x].E[0], l, G[x].E[0], i);
			r = x;
		} else {
			split(G[x].E[1], G[x].E[1], r, i-key-1);
			l = x;
		}
		update(x);
	}

	// Join two treaps in given order; O(lg n)
	int join(int l, int r) {
		push(l); push(r);
		if (l < 0 || r < 0) return max(l, r);

		if (G[l].weight < G[r].weight) {
			G[l].E[1] = join(G[l].E[1], r);
			update(l);
			return l;
		}

		G[r].E[0] = join(l, G[r].E[0]);
		update(r);
		return r;
	}

	// Find node with index i in treap x; O(lg n)
	int find(int x, int i) {
		while (x >= 0) {
			push(x);
			int key = size(G[x].E[0]);
			if (key == i) return x;
			x = G[x].E[key < i];
			if (key < i) i -= key+1;
		}
		return x;
	}

	// Reverse interval [l;r) in treap x; O(lg n)
	int reverse(int x, int l, int r) {
		int a, b, c;
		split(x, b, c, r);
		split(b, a, b, l);
		if (b >= 0) G[b].flip ^= 1;
		return join(join(a, b), c);
	}

	// Find root of treap containing x; O(lg n)
	int root(int x) {
		while (G[x].par >= 0) x = G[x].par;
		return x;
	}
};
