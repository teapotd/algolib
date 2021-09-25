#include "../../../src/graphs/weighted_matching.h"
#include "../testing.h"

pair<ll, Vi> hungarian_kactl(const vector<vector<ll>> &a) {
	if (a.empty()) return {0, {}};
	ll n = sz(a) + 1, m = sz(a[0]) + 1;
	vector<ll> u(n), v(m), p(m);
	Vi ans(n-1);
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

int main() {
	for (int t = 0; t < 100000; t++) {
		int n = r(0, 50);
		int m = r(0, 50);
		if (n > m) swap(n, m);
		if (n == 0) m = 0;

		vector<vector<ll>> cost(n, vector<ll>(m));
		each(row, cost) each(e, row) e = rl(-1e15, 1e15);

		Vi L, R;
		ll val = hungarian(cost, L, R);

		Vi kactlL;
		ll kactlVal;
		tie(kactlVal, kactlL) = hungarian_kactl(cost);
		Vi kactlR(m, -1);
		rep(i, 0, n) kactlR[kactlL[i]] = i;

		if (val != kactlVal || L != kactlL || R != kactlR) {
			deb(val, kactlVal);
			deb(L, kactlL);
			deb(R, kactlR);
			break;
		}
	}
	return 0;
}