#pragma once
#include "../template.h"

using flow_t = int;
constexpr flow_t INF = 1e9+10;

// Push-relabel algorithm for maximum flow;
// O(V^2*sqrt(E)), but very fast in practice.
// Preflow is not converted to flow!
// UNTESTED
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

	// Initialize for n vertices
	MaxFlow(int k = 0) : G(k) {}

	// Add new vertex
	int addVert() {
		G.emplace_back();
		return sz(G)-1;
	}

	// Add edge between u and v with
	// capacity cap and reverse capacity rcap
	void addEdge(int u, int v,
	             flow_t cap, flow_t rcap = 0) {
		G[u].pb({ v, sz(G[v]), 0, cap });
		G[v].pb({ u, sz(G[u])-1, 0, rcap });
	}

	void raise(int v, int h) {
		if (hei[v] < n)
			prv[nxt[prv[v]] = nxt[v]] = prv[v];
		if ((hei[v] = h) < n) {
			if (extra[v] > 0) {
				bot[v] = act[h], act[h] = v;
				high = max(high, h);
			}
			cut = max(cut, h);
			nxt[v] = nxt[prv[v] = h += n];
			prv[nxt[nxt[h] = v]] = v;
		}
	}

	void global(int t) {
		hei.assign(n, n);
		act.assign(n, -1);
		iota(all(prv), 0);
		iota(all(nxt), 0);
		hei[t] = high = cut = work = 0;
		for (Q.push(t); !Q.empty(); Q.pop()) {
			int v = Q.front();
			each(e, G[v])
				if (hei[e.to]==n && G[e.to][e.inv].rem)
					Q.push(e.to), raise(e.to, hei[v]+1);
		}
	}

	void push(int v, Edge& e) {
		auto f = min(extra[v], e.rem);
		if (f > 0) {
			if (!extra[e.to]) {
				bot[e.to] = act[hei[e.to]];
				act[hei[e.to]] = e.to;
			}
			e.rem -= f; G[e.to][e.inv].rem += f;
			extra[v] -= f; extra[e.to] += f;
		}
	}

	void discharge(int v) {
		int h = n;

		auto go = [&](int a, int b) {
			rep(i, a, b) {
				auto& e = G[v][i];
				if (e.rem) {
					if (hei[v] == hei[e.to]+1) {
						push(v, e);
						if (extra[v] <= 0)
							return arc[v] = i, 0;
					} else h = min(h, hei[e.to]+1);
				}
			}
			return 1;
		};

		if (go(arc[v], sz(G[v])) && go(0, arc[v])){
			int k = hei[v] + n;
			if (nxt[k] == prv[k]) {
				rep(j, k, cut+n+1)
					while (nxt[j] < n) raise(nxt[j], n);
				cut = k-n-1;
			} else raise(v, h), work++;
		}
	}

	// Compute maximum flow from src to dst
	flow_t maxFlow(int src, int dst) {
		extra.assign(n = sz(G), 0);
		hei.assign(n, 0);
		arc.assign(n, 0);
		prv.resize(n*2);
		nxt.resize(n*2);
		act.resize(n);
		bot.resize(n);
		each(v, G) each(e, v) e.rem = e.cap;

		extra[dst] = -(extra[src] = INF);
		each(e, G[src]) push(src, e);
		global(dst);

		for (; high; high--)
			while (act[high] != -1) {
				int v = act[high];
				act[high] = bot[v];
				if (hei[v] == high) {
					discharge(v);
					if (work > 4*n) global(dst);
				}
			}

		return extra[dst] + INF;
	}

	// Get if v belongs to cut component with src
	bool cutSide(int v) { return hei[v] >= n; }
};
