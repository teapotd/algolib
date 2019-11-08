#include "../../src/util/parallel_binsearch.h"
#include "../../src/template.h"
#include "../testing.h"

void run(int nElems, int maxVal) {
	Vi expected(nElems);
	each(e, expected) e = r(0, maxVal);

	Vi ret = multiBS(0, maxVal+1, nElems, [&](vector<Pii>& queries, vector<bool>& answers) {
		assert(sz(queries) == nElems);
		assert(sz(answers) == nElems);

		rep(i, 0, nElems) {
			if (i > 0) {
				assert(queries[i-1].x <= queries[i].x);
			}
			answers[i] = (expected[queries[i].y] >= queries[i].x);
		}
	});

	rep(i, 0, nElems) {
		if (ret[i] != expected[i]) {
			deb(ret, expected);
			exit(0);
		}
	}
}

int main() {
	rep(n, 1, 100) {
		rep(m, 2, 100) {
			run(n, m);
		}
	}

	run(int(1e6), int(1e9));
	return 0;
}
