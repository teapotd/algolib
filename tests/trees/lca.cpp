#include "../../lib/trees/lca.h"
#include "../testing.h"

Vi parents, levels;

void dfsParents(int i, int parent, int d) {
	each(e, G[i].edges) if (e != parent) dfsParents(e, i, d+1);
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

		initLCA(0);

		rep(i, 0, n) rep(j, 0, n) {
      if (G[i].level >= j) {
				assert(laq(i, j) == naiveLAQ(i, j));
			}
			assert(lca(i, j) == naiveLCA(i, j));
		}
	}
	return 0;
}
