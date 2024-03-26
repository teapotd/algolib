#pragma once
#include "../template.h"
#include "../structures/find_union_undo.h"
#include <ext/pb_ds/priority_queue.hpp>

struct Edge {
	int a, b;
	ll w;
	bool operator<(Edge r) const {
		return w > r.w;
	}
};

// Find directed minimum spanning tree
// rooted at vertex `root`; O(m log n)
// Returns weight of found spanning tree.
// par[i] = parent of i-th vertex in the tree,
// par[root] = -1
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/DirectedMST.h
ll dmst(vector<Edge>& edges,
        int n, int root, vi& par) {
	RollbackFAU dsu(n);
	vector<__gnu_pbds::priority_queue<Edge>>Q(n);
	vector<ll> delta(n);
	each(e, edges) Q[e.b].push(e);

	ll ans = 0;
	vi seen(n, -1), path(n);
	vector<Edge> ed(n), in(n, {-1, -1, 0});
	vector<tuple<int, int, vector<Edge>>> cycs;
	seen[root] = root;

	rep(s, 0, n)
		for (int u = s, pos = 0; seen[u] < 0;) {
			if (Q[u].empty()) return -1;
			auto e = Q[u].top();
			Q[u].pop();
			ans += e.w - delta[u];
			delta[u] = e.w;
			ed[pos] = in[u] = e;
			seen[path[pos++] = u] = s;
			if (seen[u = dsu.find(e.a)] == s) {
				int w, end = pos, t = dsu.time();
				while (dsu.join(u, w = path[--pos])) {
					if (sz(Q[w]) > sz(Q[u])) swap(u, w);
					for (auto f : Q[w]) {
						f.w += delta[u] - delta[w];
						Q[u].push(f);
					}
				}
				Q[w = dsu.find(u)].swap(Q[u]);
				delta[w] = delta[u];
				seen[u=w] = -1;
				cycs.pb({u, t, {&ed[pos], &ed[end]}});
			}
		}

	reverse(all(cycs));
	for (auto &[u, t, e] : cycs) {
		auto s = in[u];
		dsu.rollback(t);
		each(f, e) in[dsu.find(f.b)] = f;
		in[dsu.find(s.b)] = s;
	}
	par.resize(n);
	rep(i, 0, n) par[i] = in[i].a;
	return ans;
}
