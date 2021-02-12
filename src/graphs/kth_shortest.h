#pragma once
#include "../template.h"

constexpr ll INF = 1e18;

// Eppstein's k-th shortest path algorithm;
// time and space: O((m+k) log (m+k))
struct Eppstein {
	using T = ll; // Type for edge weights
	using Edge = pair<int, T>;

	struct Node {
		int E[2] = {}, s{0};
		Edge x;
	};

	T shortest; // Shortest path length
	priority_queue<pair<T, int>> Q;
	vector<Node> P{1};
	Vi h;

	// Initialize shortest path structure for
	// weighted graph G, source s and target t;
	// time: O(m log m)
	Eppstein(vector<vector<Edge>>& G,
	         int s, int t) {
		int n = sz(G);
		vector<vector<Edge>> H(n);
		rep(i,0,n) each(e,G[i]) H[e.x].pb({i,e.y});

		Vi ord, par(n, -1);
		vector<T> d(n, -INF);
		Q.push({d[t] = 0, t});

		while (!Q.empty()) {
			auto v = Q.top();
			Q.pop();
			if (d[v.y] == v.x) {
				ord.pb(v.y);
				each(e, H[v.y]) if (v.x-e.y > d[e.x]) {
					Q.push({d[e.x] = v.x-e.y, e.x});
					par[e.x] = v.y;
				}
			}
		}

		if ((shortest = -d[s]) >= INF) return;
		h.resize(n);

		each(v, ord) {
			int p = par[v];
			if (p+1) h[v] = h[p];
			each(e, G[v]) if (d[e.x] > -INF) {
				T k = e.y - d[e.x] + d[v];
				if (k || e.x != p)
					h[v] = push(h[v], {e.x, k});
				else
					p = -1;
			}
		}

		P[0].x.x = s;
		Q.push({0, 0});
	}

	int push(int t, Edge x) {
		P.pb(P[t]);
		if (!P[t = sz(P)-1].s || P[t].x.y >= x.y)
			swap(x, P[t].x);
		if (P[t].s) {
			int i = P[t].E[0], j = P[t].E[1];
			int d = P[i].s > P[j].s;
			int k = push(d ? j : i, x);
			P[t].E[d] = k;
		}
		P[t].s++;
		return t;
	}

	// Get next shortest path length,
	// the first call returns shortest path.
	// Returns -1 if there's no more paths;
	// time: O(log k), where k is total count
	// of nextPath calls.
	ll nextPath() {
		if (Q.empty()) return -1;
		auto v = Q.top();
		Q.pop();
		for (int i : P[v.y].E) if (i)
			Q.push({ v.x-P[i].x.y+P[v.y].x.y, i });
		int t = h[P[v.y].x.x];
		if (t) Q.push({ v.x - P[t].x.y, t });
		return shortest - v.x;
	}
};
