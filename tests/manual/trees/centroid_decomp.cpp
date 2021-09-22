#include "../../../src/trees/centroid_decomp.h"
#include "../testing.h"

vector<Vi> G;
CentroidTree cen;

void edge(int i, int j) {
	G[i-1].pb(j-1);
	G[j-1].pb(i-1);
}

void dfs(int v, int indent = 0) {
	for (int i = 0; i < indent; i++) {
		printf(" ");
	}

	printf("%d (%d/%d): ", v+1, cen.depth[v], cen.size[v]);
	printf("\n");

	each(e, cen.child[v]) dfs(e, indent+4);
}

int main() {
	G.resize(16);

	edge(1, 4);
	edge(2, 4);
	edge(3, 4);
	edge(4, 5);
	edge(5, 6);
	edge(6, 7);
	edge(7, 8);
	edge(7, 9);
	edge(6, 10);
	edge(10, 11);
	edge(11, 12);
	edge(12, 14);
	edge(11, 13);
	edge(13, 15);
	edge(13, 16);

	cen = {G};
	dfs(cen.root);

	rep(i, 0, sz(G)) {
		deb(i, cen.ind[i], cen.subtree[i], cen.dists[i], cen.neigh[i], cen.dir[i]);
	}
	return 0;
}
