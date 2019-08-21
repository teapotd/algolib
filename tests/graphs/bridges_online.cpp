#include "../../lib/graphs/bridges_online.h"
#include "../testing.h"

struct BridgesNaive {
	vector<vector<Pii>> G;
	Vi f, seen;
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

void runTest() {
	//int n = 6;
	int n = r(1, 40);
	Bridges fast(n);
	BridgesNaive naive(n);

	//deb(n);
	//cerr << '\n';

	vector<Pii> avail;
	rep(i, 0, n) rep(j, i+1, n) avail.pb({i, j});
	random_shuffle(all(avail));

	while (true) {
		switch (r(0, 3)) {
			case 0: {
				if (avail.empty()) return;
				Pii e = avail.back();
				avail.pop_back();
				fast.addEdge(e.x, e.y);
				naive.addEdge(e.x, e.y);
				//deb(0, e.x, e.y);
				break;
			}
			case 1: {
				int a = r(0, n-1), b = r(0, n-1);
				bool naiveAns = (naive.flow(a, b) >= 1);
				bool fastAns = (fast.cc[a] == fast.cc[b]);
				//deb(1, a, b, naiveAns, fastAns);
				assert(naiveAns == fastAns);
				break;
			}
			case 2: {
				int a = r(0, n-1), b = r(0, n-1);
				bool naiveAns = (naive.flow(a, b) >= 2);
				bool fastAns = (fast.bi(a) == fast.bi(b));
				//deb(2, a, b, naiveAns, fastAns);
				assert(naiveAns == fastAns);
				break;
			}
		}
	}
}

void bad() {
	Bridges fast(6);
	BridgesNaive naive(6);

	for (Pii e : vector<Pii>{ {2,3}, {1,5}, {0,2}, {4,5}, {1,4}, {0,3}, {0,5}, {0,4} }) {
		fast.addEdge(e.x, e.y);
		naive.addEdge(e.x, e.y);

		Vi comp, par;
		rep(i, 0, 6) par.pb(fast.par[i]);
		rep(i, 0, 6) comp.pb(fast.bi(i));
		deb(e, comp, par);
	}

	bool naiveAns = (naive.flow(3, 1) >= 2);
	bool fastAns = (fast.bi(3) == fast.bi(1));
	deb(naiveAns, fastAns);
}

int main() {
	rep(i, 0, 200000) {
		runTest();
	}
	return 0;
}
