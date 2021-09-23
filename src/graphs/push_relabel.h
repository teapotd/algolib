#pragma once
#include "../template.h"

using flow_t = int;

// Push-relabel algorithm for maximum flow;
// O(V^2*sqrt(E)), but very fast in practice.
struct MaxFlow {
	struct Edge {
		int to, inv;
		flow_t rem, cap;
	};

	vector<basic_string<Edge>> G;
	vector<flow_t> extra;
	Vi hei, arc, prv, nxt, act, bot;
	queue<int> Q;
	int n, high, cut, work;

	// Initialize for k vertices
	MaxFlow(int k = 0) : G(k) {}

	// Add new vertex
	int addVert() { G.pb({}); return sz(G)-1; }

	// Add edge from u to v with capacity cap
	// and reverse capacity rcap.
	// Returns edge index in adjacency list of u.
	int addEdge(int u, int v,
	            flow_t cap, flow_t rcap = 0) {
		G[u].pb({ v, sz(G[v]), 0, cap });
		G[v].pb({ u, sz(G[u])-1, 0, rcap });
		return sz(G[u])-1;
	}

	void raise(int v, int h) {
		prv[nxt[prv[v]] = nxt[v]] = prv[v];
		hei[v] = h;
		if (extra[v] > 0) {
			bot[v] = act[h]; act[h] = v;
			high = max(high, h);
		}
		if (h < n) cut = max(cut, h+1);
		nxt[v] = nxt[prv[v] = h += n];
		prv[nxt[nxt[h] = v]] = v;
	}

	void global(int s, int t) {
		hei.assign(n, n*2);
		act.assign(n*2, -1);
		iota(all(prv), 0);
		iota(all(nxt), 0);
		hei[t] = high = cut = work = 0;
		hei[s] = n;
		for (int x : {t, s})
			for (Q.push(x); !Q.empty(); Q.pop()) {
				int v = Q.front();
				each(e, G[v])
					if (hei[e.to] == n*2 &&
					    G[e.to][e.inv].rem)
						Q.push(e.to), raise(e.to,hei[v]+1);
			}
	}

	void push(int v, Edge& e, bool z) {
		auto f = min(extra[v], e.rem);
		if (f > 0) {
			if (z && !extra[e.to]) {
				bot[e.to] = act[hei[e.to]];
				act[hei[e.to]] = e.to;
			}
			e.rem -= f; G[e.to][e.inv].rem += f;
			extra[v] -= f; extra[e.to] += f;
		}
	}

	void discharge(int v) {
		int h = n*2, k = hei[v];

		rep(j, 0, sz(G[v])) {
			auto& e = G[v][arc[v]];
			if (e.rem) {
				if (k == hei[e.to]+1) {
					push(v, e, 1);
					if (extra[v] <= 0) return;
				} else h = min(h, hei[e.to]+1);
			}
			if (++arc[v] >= sz(G[v])) arc[v] = 0;
		}

		if (k < n && nxt[k+n] == prv[k+n]) {
			rep(j, k, cut) while (nxt[j+n] < n)
				raise(nxt[j+n], n);
			cut = k;
		} else raise(v, h), work++;
	}

	// Compute maximum flow from src to dst
	flow_t maxFlow(int src, int dst) {
		extra.assign(n = sz(G), 0);
		arc.assign(n, 0);
		prv.resize(n*3);
		nxt.resize(n*3);
		bot.resize(n);
		each(v, G) each(e, v) e.rem = e.cap;

		each(e, G[src])
			extra[src] = e.cap, push(src, e, 0);
		global(src, dst);

		for (; high; high--)
			while (act[high] != -1) {
				int v = act[high];
				act[high] = bot[v];
				if (v != src && hei[v] == high) {
					discharge(v);
					if (work > 4*n) global(src, dst);
				}
			}

		return extra[dst];
	}

	// Get flow through e-th edge of vertex v
	flow_t getFlow(int v, int e) {
		return G[v][e].cap - G[v][e].rem;
	}

	// Get if v belongs to cut component with src
	bool cutSide(int v) { return hei[v] >= n; }
};
