#include "../../src/graphs/biconnected.h"
#include "../testing.h"

int main() {
	vector<Vi> G(10);

	auto add = [&](int i, int j) {
		G[i].pb(j);
		G[j].pb(i);
	};

	add(0, 1);
	add(1, 2);
	add(2, 3);
	add(3, 0);

	add(1, 4);
	add(1, 5);
	add(4, 5);

	Biconnected bi(G);
	rep(v, 0, sz(bi)) deb(v, bi[v]);
	rep(c, 0, sz(bi.comps)) deb(c, bi.comps[c]);
	return 0;
}
