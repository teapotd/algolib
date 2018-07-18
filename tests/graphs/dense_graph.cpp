#include "../../lib/graphs/dense_graph.h"
#include "../testing.h"

int n = 100000/64*64;
uint64_t masks[128];
DenseGraph G(n);

void dfs(int i) {
	G.visit(i);
	G.dfsStep(i, dfs);
}

uint64_t randMask() {
	uint64_t ret = -1;
	rep(i, 0, 2) ret &= masks[rand()%128];
	return ret;
}

int main() {
	each(x, masks) x = rnd64();

	each(m, G.M) m = randMask();

	auto before = now();
	rep(i, 0, n) if (!G.isVisited(i)) dfs(i);
	cout << since(before) << "ms" << endl;
	return 0;
}
