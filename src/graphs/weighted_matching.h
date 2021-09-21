#pragma once
#include "../template.h"

// Minimum cost bipartite matching; O(n^2*m)
// Input is n x m cost matrix, where n <= m.
// Returns matching weight.
// L[i] = right vertex matched to i-th left
// R[i] = left vertex matched to i-th right
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/WeightedMatching.h
ll hungarian(const vector<vector<ll>>& cost,
             Vi& L, Vi& R) {
	if (cost.empty())
		return L.clear(), R.clear(), 0;
	int b, c = 0, n = sz(cost), m = sz(cost[0]);
	assert(n <= m);

	vector<ll> x(n), y(m+1);
	L.assign(n, -1);
	R.assign(m+1, -1);

	rep(i, 0, n) {
		vector<ll> sla(m, INT64_MAX);
		Vi vis(m+1), prv(m, -1);
		for (R[b = m] = i; R[b]+1; b = c) {
			int a = R[b];
			ll d = INT64_MAX;
			vis[b] = 1;
			rep(j, 0, m) if (!vis[j]) {
				ll cur = cost[a][j] - x[a] - y[j];
				if (cur < sla[j])
					sla[j] = cur, prv[j] = b;
				if (sla[j] < d) d = sla[j], c = j;
			}
			rep(j, 0, m+1) {
				if (vis[j]) x[R[j]] += d, y[j] -= d;
				else sla[j] -= d;
			}
		}
		while (b-m) c = b, R[c] = R[b = prv[b]];
	}

	rep(j, 0, m) if (R[j]+1) L[R[j]] = j;
	R.resize(m);
	return -y[m];
}
