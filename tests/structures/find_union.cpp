#include "../../lib/structures/find_union.h"
#include "../testing.h"

int main() {
	rep(total, 0, 10) {
		int n = r(0, 1000);
		FAU fau(n);
		Vi naive(n);
		iota(all(naive), 0);

		rep(i, 0, 100) {
			int a = r(0, n-1), b = r(0, n-1);
			fau.join(a, b);

			int from = naive[a], to = naive[b];
			each(x, naive) if (x == from) x = to;

			rep(j, 0, n) {
				int s = 0;
				rep(k, 0, n) {
					assert((naive[j] == naive[k]) == (fau.find(j) == fau.find(k)));
					if (naive[j] == naive[k]) s++;
				}
				assert(fau.size(j) == s);
			}
		}
	}
	return 0;
}
