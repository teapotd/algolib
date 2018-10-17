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

	struct Vert {
		vector<Edge> E;
		int prev;
		T add;
	};

	vector<Vert> G;

	// Initialize for n vertices
	MaxFlow(int n = 0) { init(n); }
	void init(int n) { G.assign(n, {}); }

	// Add new vertex
	int addVert() {
		G.emplace_back();
		return sz(G)-1;
	}

	// Add edge between u and v with capacity cap
	// and reverse capacity rcap
	void addEdge(int u,int v,int cap,int rcap=0){
		G[u].E.pb({ v, sz(G[v].E), 0, cap });
		G[v].E.pb({ u, sz(G[u].E)-1, 0, rcap });
	}

	// Compute maximum flow from src to dst.
	// Flow values can be found in edges,
	// vertices with `add` >= 0 belong to
	// cut component containing `s`.
	T maxFlow(int src, int dst) {
		T f = 0;

		do {
			each(v, G) v.prev = v.add = -1;
			queue<int> Q;
			Q.push(src);
			G[src].add = INF;

			while (!Q.empty()) {
				int i = Q.front();
				T m = G[i].add;
				Q.pop();

				if (i == dst) {
					while (i != src) {
						auto& e = G[i].E[G[i].prev];
						e.flow -= m;
						G[e.dst].E[e.inv].flow += m;
						i = e.dst;
					}
					f += m;
					break;
				}

				each(e, G[i].E) if (G[e.dst].add < 0) {
					if (e.flow < e.cap) {
						Q.push(e.dst);
						G[e.dst].prev = e.inv;
						G[e.dst].add = min(m,e.cap-e.flow);
					}
				}
			}
		} while (G[dst].prev != -1);

		return f;
	}
};
