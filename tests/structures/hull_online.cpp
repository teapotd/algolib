#include "../../lib/structures/hull_online.h"
#include "../testing.h"

vector<Pii> funcs;
Hull hull;

ll naiveQuery(ll x) {
	ll ret = -INF;
	each(f, funcs) ret = max(ret, f.x*x + f.y);
	return ret;
}

void check() {
	rep(i, -100, 100) {
		ll fast = hull.query(i), naive = naiveQuery(i);
//		deb(i, fast, naive);
		assert(fast == naive);
	}
}

int main() {
	rep(i, 0, 100000) {
		int a = r(-20, 20);
		int b = r(-20, 20);
		
		hull.insert(a, b);
		funcs.pb({a, b});
		check();
	}
}
