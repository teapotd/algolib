#include "../../../src/graphs/dense_dfs.h"
#include "../testing.h"

int n = 100000/64*64;
uint64_t masks[128];
DenseDFS G(n);

void dfs(int i) {
	G.setvisited(i);
	G.step(i, dfs);
}

uint64_t randMask() {
	uint64_t ret = -1;
	rep(i, 0, 2) ret &= masks[rand()%128];
	return ret;
}

int main() {
	each(x, masks) x = rnd64();
	each(m, G.G.M) m = randMask();

	auto before = now();
	rep(i, 0, n) if (!G.isvisited(i)) dfs(i);
	cout << since(before) << "ms" << endl;
	return 0;
}
