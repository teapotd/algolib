#include "../../src/util/compress_vec.h"
#include "../testing.h"

int cmp(int a, int b) {
	return (a < b ? -1 : (a > b ? 1 : 0));
}

int main() {
	rep(k, 0, 100) {
		vector<int> compressed(r(1, 20));
		vector<int*> toSort;

		each(v, compressed) {
			v = r(-100, 100);
			toSort.push_back(&v);
		}

		auto original = compressed;
		compressVec(toSort);

		each(v, compressed) assert(v >= 0 && v < sz(compressed));

		rep(i, 0, sz(compressed)) {
			rep(j, 0, sz(compressed)) {
				assert(cmp(compressed[i], compressed[j]) == cmp(original[i], original[j]));
			}
		}

		deb(original);
		deb(compressed);
		cerr << endl;
	}
	return 0;
}
