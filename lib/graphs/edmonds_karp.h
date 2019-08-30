#pragma once
#include "../template.h"

constexpr int INF = 1e9+10;

// Edmonds-Karp algorithm for finding
// maximum flow in graph; time: O(V*E^2)
// NOT HEAVILY TESTED
struct MaxFlow {
	using T = int;

	struct Edge {
		int dst, inv;
		T flow, cap;
	};

	vector<vector<Edge>> G;
	vector<T> add;
	Vi prev;

	// Initialize for n vertices
	MaxFlow(int n = 0) : G(n) {}

	// Add new vertex
	int addVert() {
		G.emplace_back(); return sz(G)-1;
	}

	// Add edge between u and v with capacity cap
	// and reverse capacity rcap
	void addEdge(int u, int v, T cap, T rcap=0) {
		G[u].pb({ v, sz(G[v]), 0, cap });
		G[v].pb({ u, sz(G[u])-1, 0, rcap });
	}

	// Compute maximum flow from src to dst.
	// Flow values can be found in edges,
	// vertices with `add` >= 0 belong to
	// cut component containing `s`.
	T maxFlow(int src, int dst) {
		T f = 0;

		do {
			queue<int> Q;
			Q.push(src);
			prev.assign(sz(G), -1);
			add.assign(sz(G), -1);
			add[src] = INF;

			while (!Q.empty()) {
				int i = Q.front();
				T m = add[i];
				Q.pop();

				if (i == dst) {
					while (i != src) {
						auto& e = G[i][prev[i]];
						e.flow -= m;
						G[e.dst][e.inv].flow += m;
						i = e.dst;
					}
					f += m;
					break;
				}

				each(e, G[i]) if (add[e.dst] < 0) {
					if (e.flow < e.cap) {
						Q.push(e.dst);
						prev[e.dst] = e.inv;
						add[e.dst] = min(m, e.cap-e.flow);
					}
				}
			}
		} while (prev[dst] != -1);

		return f;
	}
};
