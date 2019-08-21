#pragma once
#include "../template.h"

// TESTED ON RANDS
// Dynamic 2-edge connectivity queries
// Usage: Bridges bridges(vertex_count);
// - bridges.addEdge(u, v); - add edge (u, v)
// - bridges.cc[v] = connected component ID
// - bridges.bi(v) = 2-edge connected comp ID
struct Bridges {
	vector<Vi> G; // Spanning forest
	Vi cc, size, par, bp, seen;
	int cnt{0};

	Bridges(int n = 0) : G(n), cc(n), size(n, 1),
	                     par(n, -1), bp(n, -1),
	                     seen(n) {
		iota(all(cc), 0);
	}

	void addEdge(int u, int v) {
		if (cc[u] == cc[v]) {
			int r = lca(u, v);
			while ((v = root(v)) != r)
				v = bp[bi(v)] = par[v];
			while ((u = root(u)) != r)
				u = bp[bi(u)] = par[u];
		} else {
			G[u].pb(v); G[v].pb(u);
			if (size[cc[u]] > size[cc[v]]) swap(u,v);
			size[cc[v]] += size[cc[u]];
			dfs(u, v);
		}
	}

	int bi(int v) {
		return bp[v] == -1 ? v : bp[v] = bi(bp[v]);
	}

	int root(int v) {
		return par[v] == -1 || bi(par[v]) != bi(v)
			? v : par[v] = root(par[v]);
	}

	void dfs(int v, int p) {
		par[v] = p; cc[v] = cc[p];
		each(e, G[v]) if (e != p) dfs(e, v);
	}

	int lca(int u, int v) {
		for (cnt++;; swap(u, v)) if (u != -1) {
			if (seen[u = root(u)] == cnt) return u;
			seen[u] = cnt; u = par[u];
		}
	}
};
