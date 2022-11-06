#pragma once
#include "../template.h"

// Find maximum bipartite matching; time: ?
// G must be bipartite graph!
// Returns matching size (edge count).
// match[v] = vert matched to v or -1
int matching(vector<vi>& G, vi& match) {
	vector<bool> seen;
	int n = 0, k = 1;
	match.assign(sz(G), -1);

	function<int(int)> dfs = [&](int i) {
		if (seen[i]) return 0;
		seen[i] = 1;
		each(e, G[i]) {
			if (match[e] < 0 || dfs(match[e])) {
				match[i] = e; match[e] = i;
				return 1;
			}
		}
		return 0;
	};

	while (k) {
		seen.assign(sz(G), 0);
		k = 0;
		rep(i, 0, sz(G)) if (match[i] < 0)
			k += dfs(i);
		n += k;
	}
	return n;
}

// Convert maximum matching to vertex cover
// time: O(n+m)
vi vertexCover(vector<vi>& G, vi& match) {
	vi ret, col(sz(G)), seen(sz(G));

	function<void(int, int)> dfs =
			[&](int i, int c) {
		if (col[i]) return;
		col[i] = c+1;
		each(e, G[i]) dfs(e, !c);
	};

	function<void(int)> aug = [&](int i) {
		if (seen[i] || col[i] != 1) return;
		seen[i] = 1;
		each(e, G[i]) seen[e] = 1, aug(match[e]);
	};

	rep(i, 0, sz(G)) dfs(i, 0);
	rep(i, 0, sz(G)) if (match[i] < 0) aug(i);
	rep(i, 0, sz(G))
		if (seen[i] == col[i]-1) ret.pb(i);
	return ret;
}
