#include "../../../src/graphs/matching_weighted.h"
#include "../base_test.hpp"

namespace kactl {
	pair<ll, vi> hungarian(const vector<vector<ll>> &a) {
		if (a.empty()) return {0, {}};
		ll n = sz(a) + 1, m = sz(a[0]) + 1;
		vector<ll> u(n), v(m), p(m);
		vi ans(n-1);
		rep(i,1,n) {
			p[0] = i;
			ll j0 = 0; // add "dummy" worker 0
			vector<ll> dist(m, INT64_MAX), pre(m, -1);
			vector<bool> done(m + 1);
			do { // dijkstra
				done[j0] = true;
				ll i0 = p[j0], j1 = 0, delta = INT64_MAX;
				rep(j,1,m) if (!done[j]) {
					auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
					if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
					if (dist[j] < delta) delta = dist[j], j1 = j;
				}
				rep(j,0,m) {
					if (done[j]) u[p[j]] += delta, v[j] -= delta;
					else dist[j] -= delta;
				}
				j0 = j1;
			} while (p[j0]);
			while (j0) { // update alternating path
				ll j1 = pre[j0];
				p[j0] = p[j1], j0 = j1;
			}
		}
		rep(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
		return {-v[0], ans}; // min cost
	}
};

void deterministic() {
}

void fuzz() {
	rep(t, 0, 30'000) {
		int n = randInt(1, 50);
		int m = randInt(1, 50);
		if (n > m) swap(n, m);

		vector<vector<ll>> cost(n, vector<ll>(m));
		each(row, cost) each(e, row) e = randLong(-1e15, 1e15);

		vi L, R;
		ll val = hungarian(cost, L, R);

		auto [kactlVal, kactlL] = kactl::hungarian(cost);
		vi kactlR(m, -1);
		rep(i, 0, n) kactlR[kactlL[i]] = i;

		assert(val == kactlVal);
		assert(L == kactlL);
		assert(R == kactlR);
	}
}

void benchmark() {
}
