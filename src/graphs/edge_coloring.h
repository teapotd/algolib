#pragma once
#include "../template.h"

// General graph edge coloring; time: O(nm)
// Finds (D+1)-edge-coloring of given graph,
// where D is max vertex degree.
// Returns vector of edge colors `col`.
// col[i] = color of i-th edge [0..D]
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/EdgeColoring.h
Vi vizing(vector<Pii>& edges, int n) {
	Vi cc(n+1), ret(sz(edges)),
	   fan(n), fre(n), loc;
	each(e, edges) cc[e.x]++, cc[e.y]++;
	int u, v, cnt = *max_element(all(cc)) + 1;
	vector<Vi> adj(n, Vi(cnt, -1));
	each(e, edges) {
		tie(u, v) = e;
		fan[0] = v;
		loc.assign(cnt, 0);
		int at = u, end = u, d, c = fre[u],
		    ind = 0, i = 0;
		while (d = fre[v],
		       !loc[d] && (v = adj[u][d]) != -1)
			loc[d] = ++ind, cc[ind] = d, fan[ind]=v;
		cc[loc[d]] = c;
		for (int cd = d; at+1; cd ^= c ^ d,
		     at = adj[at][cd])
			swap(adj[at][cd], adj[end=at][cd^c^d]);
		while (adj[fan[i]][d] + 1) {
			int x = fan[i], y = fan[++i], f = cc[i];
			adj[u][f] = x; adj[x][f] = u;
			adj[y][f] = -1; fre[y] = f;
		}
		adj[u][d] = fan[i];
		adj[fan[i]][d] = u;
		for (int y : {fan[0], u, end})
			for (int& z = fre[y] = 0; adj[y][z]+1;)
				z++;
	}
	rep(i, 0, sz(edges))
		for (tie(u, v) = edges[i];
		     adj[u][ret[i]] != v;) ++ret[i];
	return ret;
}
