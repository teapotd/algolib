#include "../../../src/structures/max_queue.h"
#include "../testing.h"

int main() {
	Vi naive;
	MaxQueue que;

	rep(i, 0, 10000) {
		if (naive.empty() || r(0, 1)) {
			int tmp = r(0, 200);
			naive.pb(tmp);
			que.push(tmp);
		} else {
			naive.erase(naive.begin());
			que.pop();
		}

		if (!naive.empty()) {
			int gg = INT_MIN;
			each(k, naive) gg = max(gg, k);
			assert(gg == que.max());
		}
	}
	return 0;
}
