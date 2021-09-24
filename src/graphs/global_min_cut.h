#pragma once
#include "../template.h"

// Find a minimum cut in an undirected graph
// with non-negative edge weights
// given its adjacency matrix M; time: O(n^3)
// `out` contains vertices on one side.
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/GlobalMinCut.h
ll minCut(vector<vector<ll>> M, Vi& out) {
	int n = sz(M);
	ll ans = INT64_MAX;
	vector<Vi> co(n);
	rep(i, 0, n) co[i].pb(i);
	out.clear();
	rep(ph, 1, n) {
		auto w = M[0];
		size_t s = 0, t = 0;
		// O(V^2) -> O(E log V) with priority queue
		rep(it, 0, n-ph) {
			w[t] = INT64_MIN; s = t;
			t = max_element(all(w)) - w.begin();
			rep(i, 0, n) w[i] += M[t][i];
		}
		ll alt = w[t] - M[t][t];
		if (alt < ans) ans = alt, out = co[t];
		co[s].insert(co[s].end(), all(co[t]));
		rep(i, 0, n) M[s][i] += M[t][i];
		rep(i, 0, n) M[i][s] = M[s][i];
		M[0][t] = INT64_MIN;
	}
	return ans;
}
