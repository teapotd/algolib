#pragma once
#include "../template.h"

// LAQ and LCA using jump pointers
// space: O(n lg n)

struct LCA {
	vector<Vi> jumps;
	Vi level, pre, post;
	int cnt{0}, depth;

	LCA() {}

	// Initialize structure for tree G
	// and root r; time: O(n lg n)
	LCA(vector<Vi>& G, int root)
			: jumps(sz(G)), level(sz(G)),
			  pre(sz(G)), post(sz(G)) {
		dfs(G, root, root);
		depth = int(log2(sz(G))) + 2;
		rep(j, 0, depth) each(v, jumps)
			v.pb(jumps[v[j]][j]);
	}

	void dfs(vector<Vi>& G, int v, int p) {
		level[v] = p == v ? 0 : level[p]+1;
		jumps[v].pb(p);
		pre[v] = ++cnt;
		each(e, G[v]) if (e != p) dfs(G, e, v);
		post[v] = ++cnt;
	}

	// Check if a is ancestor of b; time: O(1)
	bool isAncestor(int a, int b) {
		return pre[a] <= pre[b] &&
		       post[b] <= post[a];
	}

	// Lowest Common Ancestor; time: O(lg n)
	int operator()(int a, int b) {
		for (int j = depth; j--;)
			if (!isAncestor(jumps[a][j], b))
				a = jumps[a][j];
		return isAncestor(a, b) ? a : jumps[a][0];
	}

	// Level Ancestor Query; time: O(lg n)
	int laq(int a, int lvl) {
		for (int j = depth; j--;)
			if (lvl <= level[jumps[a][j]])
				a = jumps[a][j];
		return a;
	}

	// Get distance from a to b; time: O(lg n)
	int distance(int a, int b) {
		return level[a] + level[b] -
		       level[operator()(a, b)]*2;
	}
};
