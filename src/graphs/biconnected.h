#pragma once
#include "../template.h"

// Biconnected components; time: O(n+m)
// Usage: Biconnected bi(graph);
// bi[v] = indices of components containing v
// bi.comps[i] = vertices of i-th component
// Bridges <=> components with 2 vertices
// Articulation points <=> vertices that belong
//                         to > 1 component
// Isolated vertex <=> empty component list
struct Biconnected : vector<Vi> {
	vector<Vi> comps;
	Vi S;
	int cnt{0};

	Biconnected() {}

	Biconnected(vector<Vi>& G)
			: vector<Vi>(sz(G)), S(sz(G)) {
		rep(i, 0, sz(G)) if (!S[i]) dfs(G, i, -1);
		rep(c, 0, sz(comps)) each(v, comps[c])
			at(v).pb(c);
	}

	int dfs(vector<Vi>& G, int v, int p) {
		int low = S[v] = ++cnt, t = -1;
		S.pb(v);

		each(e, G[v]) if (e != p)
			low = min(low, S[e] ?: dfs(G, e, v));

		if (p != -1 && low >= S[p]) {
			comps.emplace_back();
			for (; t != v; S.pop_back())
				comps.back().pb(t = S.back());
			comps.back().pb(p);
		}

		return low;
	}
};
