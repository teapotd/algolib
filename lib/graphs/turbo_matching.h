#pragma once
#include "../template.h"

// Find matching in bipartite graph; time: ?
struct Matching {
	vector<Vi> G; // Both sides together
	Vi match; // Matched vertices, -1 if none
	vector<bool> seen;

	// Initialize for n vertices
	Matching(int n = 0) { init(n); }
	void init(int n) { G.assign(n, {}); }

	// Add new vertex
	int addVert() {
		G.emplace_back();
		return sz(G)-1;
	}

	// Add edge between u and v
	void addEdge(int u, int v) {
		G[u].pb(v); G[v].pb(u);
	}

	bool dfs(int i) {
		if (seen[i]) return 0;
		seen[i] = 1;

		each(e, G[i]) {
			if (match[e] < 0 || dfs(match[e])) {
				match[i] = e;
				match[e] = i;
				return 1;
			}
		}
		return 0;
	}

	// Find maximum bipartite matching.
	// Returns matching size (edge count)
	int solve() {
		int n = 0, k = 1;
		match.assign(sz(G), -1);

		while (k) {
			seen.assign(sz(G), 0);
			k = 0;
			rep(i, 0, sz(G)) if (match[i] < 0)
				k += dfs(i);
			n += k;
		}
		return n;
	}
};
