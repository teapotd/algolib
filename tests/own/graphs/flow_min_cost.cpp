#include "../../../src/graphs/flow_min_cost.h"
#include "../base_test.hpp"
#include <bits/extc++.h>

namespace kactl {
	const ll INF = numeric_limits<ll>::max() / 4;
	typedef vector<ll> VL;

	struct MCMF {
		int N;
		vector<vi> ed, red;
		vector<VL> cap, flow, cost;
		vi seen;
		VL dist, pi;
		vector<pii> par;

		MCMF(int N_) :
			N(N_), ed(N_), red(N_), cap(N_, VL(N_)), flow(cap), cost(cap),
			seen(N_), dist(N_), pi(N_), par(N_) {}

		void addEdge(int from, int to, ll cap_, ll cost_) {
			this->cap[from][to] = cap_;
			this->cost[from][to] = cost_;
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

			auto relax = [&](int i, ll cap_, ll cost_, int dir) {
				ll val = di - pi[i] + cost_;
				if (cap_ && val < dist[i]) {
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

void fuzzSingle() {
	int n = randInt(2, 50);
	int m = randInt(1, min(n*(n-1)/2, 100));
	auto [s, t] = randDistinct<2>(0, n-1);

	MCMF ours(n);
	kactl::MCMF other(n);

	for (auto [u, v] : randEdges(n, m)) {
		int cap = randInt(0, 1e9);
		int cost = randInt(-1e5, 1e5);
		ours.addEdge(u, v, cap, cost);
		other.addEdge(u, v, cap, cost);
	}

	flow_t myFlow, myCost;
	bool ok = ours.maxFlow(s, t, myFlow, myCost);

	if (!other.setpi(s)) {
		assert(!ok); // Cycle
		return;
	}

	assert(ok);
	auto [otherFlow, otherCost] = other.maxflow(s, t);
	assert(myFlow == otherFlow);
	assert(myCost == otherCost);
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 30'000) {
		fuzzSingle();
	}
}

void benchmark() {
}
