#include "../../lib/util/compress_vec.h"
#include "../testing.h"

int main() {
	vector<int> tmp(20);
	vector<int*> toSort;

	each(v, tmp) {
		v = int(r(1, 10));
		toSort.push_back(&v);
	}

	each(v, tmp) cout << v << " ";
	cout << endl;

	compressVec(toSort);

	each(v, tmp) cout << v << " ";
	cout << endl;
	return 0;
}
