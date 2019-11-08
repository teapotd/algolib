#include "../../src/graphs/scc.h"
#include "../testing.h"

vector<Vi> G, inv;
Vi seen, order;
vector<Vi> comps;

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

void runTest() {
	int n = r(2, 500);
	int m = r(1, n*(n-1));

	G.assign(n, {});
	inv.assign(n, {});
	seen.assign(n, 0);
	order.clear();
	comps.clear();

	rep(i, 0, m) {
		int a = r(0, n-1), b = r(0, n-1);
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

	// deb(G);
	// deb(comps);
	// deb(scc.comps);
	assert(comps == scc.comps);
}

int main() {
	rep(i, 0, 1000) {
		runTest();
	}
	return 0;
}
