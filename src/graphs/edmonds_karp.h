#pragma once
#include "../template.h"

using flow_t = int;
constexpr flow_t INF = 1e9+10;

// Edmonds-Karp algorithm for finding
// maximum flow in graph; time: O(V*E^2)
// NOT HEAVILY TESTED
struct MaxFlow {
	struct Edge {
		int dst, inv;
		flow_t flow, cap;
	};

	vector<vector<Edge>> G;
	vector<flow_t> add;
	Vi prev;

	// Initialize for n vertices
	MaxFlow(int n = 0) : G(n) {}

	// Add new vertex
	int addVert() {
		G.emplace_back(); return sz(G)-1;
	}

	// Add edge between u and v with capacity cap
	// and reverse capacity rcap
	void addEdge(int u, int v,
	             flow_t cap, flow_t rcap = 0) {
		G[u].pb({ v, sz(G[v]), 0, cap });
		G[v].pb({ u, sz(G[u])-1, 0, rcap });
	}

	// Compute maximum flow from src to dst.
	// Flow values can be found in edges,
	// vertices with `add` >= 0 belong to
	// cut component containing `s`.
	flow_t maxFlow(int src, int dst) {
		flow_t i, m, f = 0;
		each(v, G) each(e, v) e.flow = 0;

	nxt:
		queue<int> Q;
		Q.push(src);
		prev.assign(sz(G), -1);
		add.assign(sz(G), -1);
		add[src] = INF;

		while (!Q.empty()) {
			m = add[i = Q.front()];
			Q.pop();

			if (i == dst) {
				while (i != src) {
					auto& e = G[i][prev[i]];
					e.flow -= m;
					G[i = e.dst][e.inv].flow += m;
				}
				f += m;
				goto nxt;
			}

			each(e, G[i])
				if (add[e.dst] < 0 && e.flow < e.cap) {
					Q.push(e.dst);
					prev[e.dst] = e.inv;
					add[e.dst] = min(m, e.cap-e.flow);
				}
		}

		return f;
	}

	// Get if v belongs to cut component with src
	bool cutSide(int v) {
		return add[v] >= 0;
	}
};
