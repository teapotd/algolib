#pragma once
#include "../template.h"

using flow_t = ll;
constexpr flow_t INF = 1e18;

// Min cost max flow using cheapest paths;
// time: O(nm + |f|*(m log n))
// or O(|f|*(m log n)) if costs are nonnegative
struct MCMF {
	struct Edge {
		int dst, inv;
		flow_t flow, cap, cost;
	};

	vector<vector<Edge>> G;
	vector<flow_t> add;

	// Initialize for n vertices
	MCMF(int n = 0) : G(n) {}

	// Add new vertex
	int addVert() { G.pb({}); return sz(G)-1; }

	// Add edge from u to v.
	// Returns edge index in adjacency list of u.
	int addEdge(int u, int v,
	            flow_t cap, flow_t cost) {
		G[u].pb({ v, sz(G[v]), 0, cap, cost });
		G[v].pb({ u, sz(G[u])-1, 0, 0, -cost });
		return sz(G[u])-1;
	}

	// Compute minimum cost maximum flow
	// from src to dst. `f` is set to flow value,
	// `c` is set to total cost value.
	// Returns false iff negative cycle
	// is reachable from from source.
	bool maxFlow(int src, int dst,
	             flow_t& f, flow_t& c) {
		flow_t i, m, d;
		f = c = 0;
		each(v, G) each(e, v) e.flow = 0;

	#if FLOW_NONNEGATIVE_COSTS
		vector<flow_t> pot(sz(G));
	#else
		// Bellman-Ford O(n*m)
		vector<flow_t> pot(sz(G), INF);
		pot[src] = 0;
		int it = sz(G), ch = 1;
		while (ch-- && it--)
			rep(s, 0, sz(G)) if (pot[s] != INF)
				each(e, G[s]) if (e.cap)
					if ((d = pot[s]+e.cost) < pot[e.dst])
						pot[e.dst] = d, ch = 1;
		if (it < 0) return 0;
	#endif

	nxt:
		vi prev(sz(G), -1);
		vector<flow_t> dist(sz(G), INF);
		priority_queue<pair<flow_t, int>> Q;
		add.assign(sz(G), -1);
		Q.push({0, src});
		add[src] = INF;
		dist[src] = 0;

		while (!Q.empty()) {
			tie(d, i) = Q.top();
			Q.pop();
			if (d != -dist[i]) continue;
			m = add[i];

			if (i == dst) {
				f += m;
				c += m * (dist[i]-pot[src]+pot[i]);
				while (i != src) {
					auto& e = G[i][prev[i]];
					e.flow -= m;
					G[i = e.dst][e.inv].flow += m;
				}
				rep(j, 0, sz(G))
					pot[j] = min(pot[j]+dist[j], INF);
				goto nxt;
			}

			each(e, G[i]) if (e.flow < e.cap) {
				d = dist[i]+e.cost+pot[i]-pot[e.dst];
				if (d < dist[e.dst]) {
					Q.push({-d, e.dst});
					prev[e.dst] = e.inv;
					add[e.dst] = min(m, e.cap-e.flow);
					dist[e.dst] = d;
				}
			}
		}
		return 1;
	}

	// Get flow through e-th edge of vertex v
	flow_t getFlow(int v, int e) {
		return G[v][e].flow;
	}

	// Get if v belongs to cut component with src
	bool cutSide(int v) { return add[v] >= 0; }
};
