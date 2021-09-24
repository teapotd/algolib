#include <bits/extc++.h>
#include "../../../src/graphs/min_cost_max_flow.h"
#include "../testing.h"

namespace kactl {
	const ll INF = numeric_limits<ll>::max() / 4;
	typedef vector<ll> VL;

	struct MCMF {
		int N;
		vector<Vi> ed, red;
		vector<VL> cap, flow, cost;
		Vi seen;
		VL dist, pi;
		vector<Pii> par;

		MCMF(int N) :
			N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
			seen(N), dist(N), pi(N), par(N) {}

		void addEdge(int from, int to, ll cap, ll cost) {
			this->cap[from][to] = cap;
			this->cost[from][to] = cost;
			ed[from].push_back(to);
			red[to].push_back(from);
		}

		void path(int s) {
			fill(all(seen), 0);
			fill(all(dist), INF);
			dist[s] = 0; ll di;

			__gnu_pbds::priority_queue<pair<ll, int>> q;
			vector<decltype(q)::point_iterator> its(N);
			q.push({0, s});

			auto relax = [&](int i, ll cap, ll cost, int dir) {
				ll val = di - pi[i] + cost;
				if (cap && val < dist[i]) {
					dist[i] = val;
					par[i] = {s, dir};
					if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
					else q.modify(its[i], {-dist[i], i});
				}
			};

			while (!q.empty()) {
				s = q.top().second; q.pop();
				seen[s] = 1; di = dist[s] + pi[s];
				for (int i : ed[s]) if (!seen[i])
					relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
				for (int i : red[s]) if (!seen[i])
					relax(i, flow[i][s], -cost[i][s], 0);
			}
			rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
		}

		pair<ll, ll> maxflow(int s, int t) {
			ll totflow = 0, totcost = 0;
			while (path(s), seen[t]) {
				ll fl = INF;
				for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
					fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
				totflow += fl;
				for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
					if (r) flow[p][x] += fl;
					else flow[x][p] -= fl;
			}
			rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
			return {totflow, totcost};
		}

		// If some costs can be negative, call this before maxflow:
		bool setpi(int s) { // (otherwise, leave this out)
			fill(all(pi), INF); pi[s] = 0;
			int it = N, ch = 1; ll v;
			while (ch-- && it--)
				rep(i,0,N) if (pi[i] != INF)
					for (int to : ed[i]) if (cap[i][to])
						if ((v = pi[i] + cost[i][to]) < pi[to])
							pi[to] = v, ch = 1;
			return it >= 0;
		}
	};
};

void runTest() {
	int n = r(2, 30);
	int m = r(1, n*(n-1)/2);
	int s = r(0, n-1);
	int t;

	do {
		t = r(0, n-1);
	} while (t == s);

	MCMF mine(n);
	kactl::MCMF other(n);

	vector<Pii> edges;
	rep(i, 0, n) rep(j, i+1, n) edges.pb({i, j});
	shuffle(all(edges), rnd);
	edges.resize(m);

	each(e, edges) {
		int cap = r(0, 1e9);
		int cost = r(-1e5, 1e5);
		mine.addEdge(e.x, e.y, cap, cost);
		other.addEdge(e.x, e.y, cap, cost);
	}

	flow_t myFlow, myCost, otherFlow, otherCost;
	bool ok = mine.maxFlow(s, t, myFlow, myCost);

	if (!other.setpi(s)) {
		deb("cycle");
		assert(!ok);
		return;
	}

	assert(ok);
	tie(otherFlow, otherCost) = other.maxflow(s, t);
	assert(myFlow == otherFlow);
	assert(myCost == otherCost);
	deb(myFlow, myCost);
}

int main() {
	rep(i, 0, 1000) {
		runTest();
	}
	return 0;
}
