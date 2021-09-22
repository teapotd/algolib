#include "../../../src/structures/rmq.h"
#include "../testing.h"

void run() {
	int n = r(1, 500);

	Vi elems(n);
	each(x, elems) x = r(-1000, 1000);

	RMQ rmq(elems);

	rep(b, 0, n+1) {
		int cur = rmq.ID;
		rep(e, 0, n+1) {
			assert(cur == rmq.query(b, e));
			if (e >= b) cur = min(cur, elems[e]);
		}
	}
}

int main() {
	rep(i, 0, 100) {
		run();
	}
}
