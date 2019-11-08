#pragma once
#include "../template.h"

using flow_t = int;
constexpr flow_t INF = 1e9+10;

// Push-relabel algorithm with global relabel
// heuristic for finding maximum flow; O(V^3),
// but very fast in practice.
// Preflow is not converted to flow!
struct MaxFlow {
	struct Vert {
		int head{0}, cur{0}, label;
		flow_t excess;
	};

	struct Edge {
		int dst, nxt;
		flow_t avail, cap;
	};

	vector<Vert> V;
	vector<Edge> E;
	queue<int> que, bfs;

	// Initialize for n vertices
	MaxFlow(int n = 0) {
		V.assign(n, {});
		E.resize(2);
	}

	// Add new vertex
	int addVert() {
		V.emplace_back();
		return sz(V)-1;
	}

	// Add edge between u and v with capacity cap
	// and reverse capacity rcap
	void addEdge(int u, int v,
	             flow_t cap, flow_t rcap = 0) {
		E.pb({ v, V[u].head, 0, cap });
		E.pb({ u, V[v].head, 0, rcap });
		V[u].head = sz(E)-2;
		V[v].head = sz(E)-1;
	}

	void push(int v, int e) {
		flow_t f = min(V[v].excess, E[e].avail);
		E[e].avail -= f;
		E[e^1].avail += f;
		V[v].excess -= f;
		if ((V[E[e].dst].excess += f) == f)
			que.push(E[e].dst);
	}

	// Compute maximum flow from src to dst
	flow_t maxFlow(int src, int dst) {
		each(v, V) v.excess = v.label = v.cur = 0;
		each(e, E) e.avail = max(e.cap, flow_t(0));

		int cnt, n = cnt = V[src].label = sz(V);
		V[src].excess = INF;
		for (int e = V[src].head; e; e = E[e].nxt)
			push(src, e);

		for (; !que.empty(); que.pop()) {
			if (cnt >= n/2) {
				each(v, V) v.label = n;
				V[dst].label = 0;
				bfs.push(dst);
				cnt = 0;

				for (; !bfs.empty(); bfs.pop()) {
					auto& v = V[bfs.front()];
					for (int e=v.head; e; e = E[e].nxt) {
						int x = E[e].dst;
						if (E[e^1].avail &&
						    V[x].label > v.label+1) {
							V[x].label = v.label+1;
							bfs.push(x);
						}
					}
				}
			}

			int v = que.front(), &l = V[v].label;
			if (v == dst) continue;

			while (V[v].excess && l < n) {
				if (!V[v].cur) {
					l = n;
					for (int e=V[v].head; e; e=E[e].nxt){
						if (E[e].avail)
							l = min(l, V[E[e].dst].label+1);
					}
					V[v].cur = V[v].head;
					cnt++;
				}

				int e = V[v].cur;
				V[v].cur = E[e].nxt;
				if (E[e].avail &&
					l == V[E[e].dst].label+1) push(v, e);
			}
		}

		return V[dst].excess;
	}

	// Get if v belongs to cut component with src
	bool cutSide(int v) {
		return V[v].label >= sz(V);
	}
};
