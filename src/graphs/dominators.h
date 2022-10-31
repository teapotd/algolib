#pragma once
#include "../template.h"

// Tarjan's algorithm for finding dominators
// in directed graph; time: O(m log n)
// Returns array of immediate dominators idom.
// idom[root] = root
// idom[v] = -1 if v is unreachable from root
vi dominators(const vector<vi>& G, int root) {
	int n = sz(G);
	vector<vi> in(n), bucket(n);
	vi pre(n, -1), anc(n, -1), par(n), best(n);
	vi ord, idom(n, -1), sdom(n, n), rdom(n);

	function<void(int,int)> dfs =
		[&](int v, int p) {
			if (pre[v] == -1) {
				par[v] = p;
				pre[v] = sz(ord);
				ord.pb(v);
				each(e, G[v]) in[e].pb(v), dfs(e, v);
			}
		};

	function<pii(int)> find = [&](int v) {
		if (anc[v] == -1) return pii(best[v], v);
		int b; tie(b, anc[v]) = find(anc[v]);
		if (sdom[b] < sdom[best[v]]) best[v] = b;
		return pii(best[v], anc[v]);
	};

	rdom[root] = idom[root] = root;
	iota(all(best), 0);
	dfs(root, -1);

	rep(i, 0, sz(ord)) {
		int v = ord[sz(ord)-i-1], b = pre[v];
		each(e, in[v])
			b = min(b, pre[e] < pre[v] ? pre[e] :
			           sdom[find(e).x]);
		each(u, bucket[v]) rdom[u] = find(u).x;
		sdom[v] = b;
		anc[v] = par[v];
		bucket[ord[sdom[v]]].pb(v);
	}

	each(v, ord) idom[v] = (rdom[v] == v ?
		ord[sdom[v]] : idom[rdom[v]]);
	return idom;
}
