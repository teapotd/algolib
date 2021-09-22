#include "../../../src/trees/lca_linear.h"
#include "../testing.h"

vector<Vi> G;
Vi parents, levels;

void dfsParents(int i, int parent, int d) {
	each(e, G[i]) if (e != parent) dfsParents(e, i, d+1);
	parents[i] = parent;
	levels[i] = d;
}

int naiveLAQ(int i, int level) {
	while (levels[i] > level) i = parents[i];
	return i;
}

int naiveLCA(int i, int j) {
	while (i != j) {
		if (levels[i] < levels[j]) swap(i, j);
		i = parents[i];
	}
	return i;
}

void bench() {
	G.resize(1e6);

	rep(i, 1, sz(G)) {
		G[i].pb(i-1);
		G[i-1].pb(i);
	}

	deb("tree generated");
	LCA lca(G, 0);
	deb("lca initialized");

	int j = 0;

	rep(i, 0, int(1e8)) {
		assert(lca.laq(sz(G)-1, j) == j);
		if (++j >= sz(G)) j = 0;
	}
}

int main() {
  rep(times, 0, 100) {
    G.clear();
    parents.clear();
    levels.clear();

    int n = r(1, 1000);
		G.resize(n);
		generateTree(G);

		parents.resize(n);
		levels.resize(n);
		dfsParents(0, -1, 0);

		LCA lca(G, 0);

		rep(i, 0, n) rep(j, 0, n) {
			if (levels[i] >= j) {
				assert(lca.laq(i, j) == naiveLAQ(i, j));
			}
			assert(lca(i, j) == naiveLCA(i, j));
		}
	}
	return 0;
}
