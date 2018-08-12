#include "../../lib/trees/centroid_decomp.h"
#include "../testing.h"

void edge(int i, int j) {
	G[i-1].E.pb(j-1);
	G[j-1].E.pb(i-1);
}

void dfs(int v, int indent = 0) {
	for (int i = 0; i < indent; i++) {
		printf(" ");
	}

	printf("%d (%d/%d): ", v+1, G[v].cDepth, G[v].cSize);
	printf("\n");

	each(e, G[v].cE) dfs(e, indent+4);
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

	dfs(centroidDecomp(0));

	rep(i, 0, sz(G)) {
		deb(i, G[i].cLinks, G[i].cSubtree, G[i].cDists);
	}
	return 0;
}
