#include "../../src/util/bit_hacks.h"
#include "../../src/template.h"
#include "../testing.h"

int at(array<ull, 64>& mat, int x, int y) {
	return (mat[x] >> y) & 1;
}

void printMatrices(array<ull, 64>& mat, array<ull, 64>& mat2) {
	rep(i, 0, 8) {
		rep(j, 0, 8) cout << ((mat[i] >> j) & 1);
		cout << ' ';
		rep(j, 0, 8) cout << ((mat2[i] >> j) & 1);
		cout << endl;
	}
	cout << endl;
}

void transpose64_test() {
	rep(i, 0, 100) {
		array<ull, 64> matrix;
		each(row, matrix) row = rnd64();

		auto transp = matrix;
		transpose64(transp);

		rep(x, 0, 64) rep(y, 0, 64) {
			assert(at(matrix, x, y) == at(transp, y, x));
		}
	}
}

void bench_transpose64() {
	constexpr int TIMES = 10000000;

	array<ull, 64> matrix;
	each(row, matrix) row = rnd64();

	auto before = now();
	rep(i, 0, TIMES) transpose64(matrix);
	cout << "transpose64: " << double(since(before))/1000 << "s" << endl;
}

int main() {
	transpose64_test();
	bench_transpose64();
	return 0;
}
