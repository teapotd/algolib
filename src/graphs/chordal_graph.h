#pragma once
#include "../template.h"
//! Source: https://github.com/jacynkaa/kactl/blob/main/content/graph/ChordalGraph.h

vi perfectEliminationOrder(vector<vi>& g) {
	int top = 0, n = sz(g);
	vi ord, vis(n), indeg(n);
	vector<vi> bucket(n);
	rep(i, 0, n) bucket[0].push_back(i);
	for (int i = 0; i < n;) {
		while(bucket[top].empty()) --top;
		int u = bucket[top].back();
		bucket[top].pop_back();
		if(vis[u]) continue;
		ord.push_back(u);
		vis[u] = 1;
		++i;
		each(v, g[u]) {
			if (vis[v]) continue;
			bucket[++indeg[v]].push_back(v);
			top = max(top, indeg[v]);
		}
	}
	reverse(all(ord));
	return ord;
}

bool isChordal(vector<vi>& g, vi ord) {
	int n = sz(g);
	set<pii> edg;
	rep(i, 0, n) each(v, g[i]) edg.insert({i,v});
	vi pos(n); rep(i, 0, n) pos[ord[i]] = i;
	rep(u, 0, n) {
		int mn = n;
		each(v, g[u]) if (pos[u] < pos[v])
			mn = min(mn, pos[v]);
		if (mn != n) {
			int p = ord[mn];
			each(v, g[u]) if (pos[v] > pos[u]
				&& v != p && !edg.count({v, p}))
					return 0;
		}
	}
	return 1;
}
