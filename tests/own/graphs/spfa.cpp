#include "../../../src/graphs/spfa.h"
#include "../testing.hpp"

vector<ll> bellmanFord(const vector<tuple<int, int, ll>>& edges, int n, int src) {
	vector<ll> dist(n, INT64_MAX);
	dist[src] = 0;

	rep(i, 0, n) {
		for (auto [u, v, d] : edges) {
			if (dist[u] != INT64_MAX) {
				dist[v] = min(dist[v], dist[u]+d);
			}
		}
	}

	for (auto [u, v, d] : edges) {
		if (dist[u] != INT64_MAX && dist[v] > dist[u]+d) {
			return {};
		}
	}

	return dist;
}

void deterministic() {
}

void fuzz() {
	rep(times, 0, 100'000) {
		int n = randInt(1, 30);
		int m = randInt(0, 100);
		int src = randInt(0, n-1);

		int minW = randInt(-100, 100);
		int maxW = randInt(-100, 100);
		if (minW > maxW) {
			swap(minW, maxW);
		}

		vector<tuple<int, int, ll>> edges;
		vector<vector<Edge>> adj(n);

		rep(i, 0, m) {
			int u = randInt(0, n-1);
			int v = randInt(0, n-1);
			int w = randInt(minW, maxW);
			edges.pb({u, v, w});
			adj[u].pb({v, w});
		}

		vi par;
		auto fast = spfa(adj, par, src);
		auto naive = bellmanFord(edges, n, src);
		assert(fast == naive);
	}
}

void benchmark() {
}
