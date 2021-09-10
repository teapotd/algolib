#pragma once
#include "../template.h"

// Biconnected components; time: O(n+m)
// Usage: Biconnected bi(graph);
// bi[v] = indices of components containing v
// bi.verts[i] = vertices of i-th component
// bi.edges[i] = edges of i-th component
// Bridges <=> components with 2 vertices
// Articulation points <=> vertices that belong
//                         to > 1 component
// Isolated vertex <=> empty component list
struct Biconnected : vector<Vi> {
	vector<Vi> verts;
	vector<vector<Pii>> edges;
	vector<Pii> S;

	Biconnected() {}

	Biconnected(vector<Vi>& G) : S(sz(G)) {
		resize(sz(G));
		rep(i, 0, sz(G)) S[i].x ?: dfs(G, i, -1);
		rep(c, 0, sz(verts)) each(v, verts[c])
			at(v).pb(c);
	}

	int dfs(vector<Vi>& G, int v, int p) {
		int low = S[v].x = sz(S)-1;
		S.pb({v, -1});

		each(e, G[v]) if (e != p) {
			if (S[e].x < S[v].x) S.pb({v, e});
			low = min(low, S[e].x ?: dfs(G, e, v));
		}

		if (p+1 && low >= S[p].x) {
			verts.pb({p}); edges.pb({});
			rep(i, S[v].x, sz(S)) {
				if (S[i].y == -1)
					verts.back().pb(S[i].x);
				else
					edges.back().pb(S[i]);
			}
			S.resize(S[v].x);
		}

		return low;
	}
};
