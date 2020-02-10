#include "../../src/trees/heavylight_decomp.h"
#include "../testing.h"

vector<Vi> G;
Vi parents, levels, vals;

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

int naiveQuery(int i, int j) {
	int ret = SegTree::ID;
	while (i != j) {
		if (levels[i] < levels[j]) swap(i, j);
		ret = SegTree::merge(ret, vals[i]);
		i = parents[i];
	}
	return ret;
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

		vals.resize(n);
		each(v, vals) v = r(1, 1000000);

		HLD hld(G, 0);

		rep(i, 0, n) {
			hld.tree.set(hld.pos[i], vals[i]);
		}

		rep(i, 0, n) rep(j, 0, n) {
			if (hld.depth[i] >= j) {
				assert(hld.laq(i, j) == naiveLAQ(i, j));
			}
			assert(hld.lca(i, j) == naiveLCA(i, j));
			assert(hld.queryPath(i, j) == naiveQuery(i, j));
		}
	}
	return 0;
}
