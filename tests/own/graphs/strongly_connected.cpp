#include "../../../src/graphs/strongly_connected.h"
#include "../base_test.hpp"

vector<vi> G, inv;
vi seen, order;
vector<vi> comps;

void dfsOrder(int v) {
	if (seen[v] >= 1) return;
	seen[v] = 1;
	each(e, G[v]) dfsOrder(e);
	order.pb(v);
}

void dfs(int v) {
	if (seen[v] >= 2) return;
	seen[v] = 2;
	comps.back().pb(v);
	each(e, inv[v]) dfs(e);
}

void fuzzSingle() {
	int n = randInt(2, 100);
	int m = randInt(1, min(n*(n-1), 1000));

	G.assign(n, {});
	inv.assign(n, {});
	seen.assign(n, 0);
	order.clear();
	comps.clear();

	rep(i, 0, m) {
		int a = randInt(0, n-1), b = randInt(0, n-1);
		G[a].pb(b);
		inv[b].pb(a);
	}

	rep(i, 0, n) dfsOrder(i);

	while (!order.empty()) {
		int v = order.back();
		order.pop_back();
		if (seen[v] >= 2) continue;

		comps.emplace_back();
		dfs(v);
	}

	SCC scc(G);

	each(v, scc.comps) sort(all(v));
	each(v, comps) sort(all(v));
	sort(all(scc.comps));
	sort(all(comps));

	assert(comps == scc.comps);
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 30'000) {
		fuzzSingle();
	}
}

void benchmark() {
}
