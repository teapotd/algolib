#include "../../../src/graphs/gomory_hu.h"
#include "../base_test.hpp"

int dfs(const vector<vector<pii>>& tree, int v, int dst, int p) {
	if (v == dst) {
		return INT_MAX;
	}

	each(e, tree[v]) if (e.x != p) {
		int ret = dfs(tree, e.x, dst, v);
		if (ret != -1) {
			return min(ret, e.y);
		}
	}

	return -1;
}

void fuzzSingle() {
	int n = randInt(2, 20);
	int m = randInt(1, n*(n-1)/2);

	vector<Edge> edges(m);

	each(e, edges) {
		e.a = randInt(0, n-1);
		e.b = randInt(0, n-1);
		e.w = randInt(0, 10);
	}

	auto treeEdges = gomoryHu(edges, n);
	vector<vector<pii>> tree(n);

	each(e, treeEdges) {
		tree[e.a].pb({e.b, e.w});
		tree[e.b].pb({e.a, e.w});
	}

	MaxFlow flow(n);
	each(e, edges) flow.addEdge(e.a, e.b, e.w, e.w);

	rep(i, 0, n) rep(j, 0, n) if (i != j) {
		int expected = flow.maxFlow(i, j);
		int got = dfs(tree, i, j, -1);
		if (expected != got) {
			deb(i, j, expected, got);
		}
	}
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 1000) {
		fuzzSingle();
	}
}

void benchmark() {
}
