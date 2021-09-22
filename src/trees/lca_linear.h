#pragma once
#include "../template.h"

// LAQ and LCA using jump pointers
// with linear memory; space: O(n)
struct LCA {
	Vi par, jmp, depth, pre, post;
	int cnt{0};

	LCA() {}

	// Initialize structure for tree G
	// and root v; time: O(n lg n)
	LCA(vector<Vi>& G, int v)
			: par(sz(G), -1), jmp(sz(G), v),
				depth(sz(G)), pre(sz(G)), post(sz(G)) {
		dfs(G, v);
	}

	void dfs(vector<Vi>& G, int v) {
		int j = jmp[v], k = jmp[j], x =
			depth[v]+depth[k] == depth[j]*2 ? k : v;
		pre[v] = ++cnt;
		each(e, G[v]) if (!pre[e]) {
			par[e] = v; jmp[e] = x;
			depth[e] = depth[v]+1;
			dfs(G, e);
		}
		post[v] = ++cnt;
	}

	// Level Ancestor Query; time: O(lg n)
	int laq(int v, int d) {
		while (depth[v] > d)
			v = depth[jmp[v]] < d ? par[v] : jmp[v];
		return v;
	}

	// Lowest Common Ancestor; time: O(lg n)
	int operator()(int a, int b) {
		if (depth[a] > depth[b]) swap(a, b);
		b = laq(b, depth[a]);
		while (a != b) {
			if (jmp[a] == jmp[b])
				a = par[a], b = par[b];
			else
				a = jmp[a], b = jmp[b];
		}
		return a;
	}

	// Check if a is ancestor of b; time: O(1)
	bool isAncestor(int a, int b) {
		return pre[a] <= pre[b] &&
		       post[b] <= post[a];
	}

	// Get distance from a to b; time: O(lg n)
	int distance(int a, int b) {
		return depth[a] + depth[b] -
		       depth[operator()(a, b)]*2;
	}

	// Get k-th vertex on path from a to b,
	// a is 0, b is last; time: O(lg n)
	// Returns -1 if k > distance(a, b)
	int kthVertex(int a, int b, int k) {
		int c = operator()(a, b);
		if (depth[a]-k >= depth[c])
			return laq(a, depth[a]-k);
		k += depth[c]*2 - depth[a];
		return (k > depth[b] ? -1 : laq(b, k));
	}
};
