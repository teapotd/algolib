#pragma once
#include "../template.h"

// Bosek's algorithm for partially online
// bipartite maximum matching - white vertices
// are fixed, black vertices are added
// one by one; time: O(E*sqrt(V))
// Usage: Matching match(num_white);
// match[v] = index of black vertex matched to
//            white vertex v or -1 if unmatched
// match.add(indices_of_white_neighbours);
// Black vertices are indexed in order they
// were added, the first black vertex is 0.
struct Matching : Vi {
	vector<Vi> adj;
	Vi rank, low, pos, vis, seen;
	int k{0};

	// Initialize structure for n white vertices
	Matching(int n = 0) : Vi(n, -1), rank(n) {}

	// Add new black vertex with its neighbours
	// given by `vec`. Returns true if maximum
	// matching is increased by 1.
	bool add(Vi vec) {
		adj.pb(move(vec));
		low.pb(0); pos.pb(0); vis.pb(0);
		if (!adj.back().empty()) {
			int i = k;
		nxt:
			seen.clear();
			if (dfs(sz(adj)-1, ++k-i)) return 1;
			each(v, seen) each(e, adj[v])
				if (rank[e] < 1e9 && vis[at(e)] < k)
					goto nxt;
			each(v, seen) each(w, adj[v])
				rank[w] = low[v] = 1e9;
		}
		return 0;
	}

	bool dfs(int v, int g) {
		if (vis[v] < k) vis[v] = k, seen.pb(v);
		while (low[v] < g) {
			int e = adj[v][pos[v]];
			if (at(e) != v && low[v] == rank[e]) {
				rank[e]++;
				if (at(e) == -1 || dfs(at(e), rank[e]))
					return at(e) = v, 1;
			} else if (++pos[v] == sz(adj[v])) {
				pos[v] = 0; low[v]++;
			}
		}
		return 0;
	}
};
