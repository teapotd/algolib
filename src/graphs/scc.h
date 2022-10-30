#pragma once
#include "../template.h"

// Tarjan's SCC algorithm; time: O(n+m)
// Usage: SCC scc(graph);
// scc[v] = index of SCC for vertex v
// scc.comps[i] = vertices of i-th SCC
// Components are in reversed topological order
struct SCC : vi {
	vector<vi> comps;
	vi S;

	SCC() {}

	SCC(vector<vi>& G) : vi(sz(G),-1), S(sz(G)) {
		rep(i, 0, sz(G)) if (!S[i]) dfs(G, i);
	}

	int dfs(vector<vi>& G, int v) {
		int low = S[v] = sz(S);
		S.pb(v);

		each(e, G[v]) if (at(e) < 0)
			low = min(low, S[e] ?: dfs(G, e));

		if (low == S[v]) {
			comps.pb({});
			rep(i, S[v], sz(S)) {
				at(S[i]) = sz(comps)-1;
				comps.back().pb(S[i]);
			}
			S.resize(S[v]);
		}

		return low;
	}
};
