#include "../../../src/graphs/bridges_online.h"
#include "../base_test.hpp"

struct BridgesNaive {
	vector<vector<pii>> G;
	vi f, seen;
	int nEdges{0};

	BridgesNaive(int n) : G(n) {}

	void addEdge(int u, int v) {
		G[u].pb({v, nEdges++});
		G[v].pb({u, nEdges++});
	}

	int flow(int u, int v) {
		f.assign(nEdges, 0);
		seen.assign(sz(G), 0);
		if (!dfs(u, v, 1)) return 0;
		if (!dfs(u, v, 2)) return 1;
		return 2;
	}

	bool dfs(int u, int v, int cnt) {
		if (u == v) return true;
		if (seen[u] == cnt) return false;
		seen[u] = cnt;

		each(e, G[u]) {
			if (f[e.y] < 1 && dfs(e.x, v, cnt)) {
				f[e.y]++;
				f[e.y^1]--;
				return true;
			}
		}

		return false;
	}
};

void fuzzSingle() {
	int n = randInt(1, 40);
	Bridges fast(n);
	BridgesNaive naive(n);

	vector<pii> avail;
	rep(i, 0, n) rep(j, i+1, n) avail.pb({i, j});
	randShuffle(avail);

	while (true) {
		switch (randInt(0, 3)) {
			case 0: {
				if (avail.empty()) return;
				auto [u, v] = avail.back();
				avail.pop_back();
				fast.addEdge(u, v);
				naive.addEdge(u, v);
				break;
			}
			case 1: {
				int a = randInt(0, n-1), b = randInt(0, n-1);
				bool naiveAns = (naive.flow(a, b) >= 1);
				bool fastAns = (fast.cc[a] == fast.cc[b]);
				assert(naiveAns == fastAns);
				break;
			}
			case 2: {
				int a = randInt(0, n-1), b = randInt(0, n-1);
				bool naiveAns = (naive.flow(a, b) >= 2);
				bool fastAns = (fast.bi(a) == fast.bi(b));
				assert(naiveAns == fastAns);
				break;
			}
		}
	}
}

void deterministic() {
}

void fuzz() {
	rep(i, 0, 2000) {
		fuzzSingle();
	}
}

void benchmark() {
	constexpr int N = 2e5;
	auto edges = randEdges(N, 1e6);

	measure("addEdge N=2e5 M=1e6", 5, [&] {
		Bridges ds(N);
		each(e, edges) ds.addEdge(e.x, e.y);
		consume(&ds);
	});
}
