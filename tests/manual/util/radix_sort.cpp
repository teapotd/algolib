#include "../../../src/util/radix_sort.h"
#include "../../../src/template.h"
#include "../testing.h"

int main() {
	rep(j, 0, 1000) {
		int n = r(1, 10000);
		int k = r(1, 10000);

		vector<pii> data(n);
		each(p, data) {
			p.x = r(1, k);
			p.y = r(1, k);
		}

		vi orderRadix = radixSort(data, k);
		vi order(n);
		iota(all(order), 0);
		stable_sort(all(order), [&](int l, int r) { return data[l] < data[r]; });

		assert(order == orderRadix);
	}
	return 0;
}
