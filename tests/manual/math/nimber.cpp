#include "../../../src/math/nimber.h"
#include "../testing.h"

int main() {
	rep(i, 0, 16) {
		rep(j, 0, 16) {
			cout << setw(3) << nimMul(i, j) << ' ';
		}
		cout << endl;
	}

	rep(i, 1, 1000) {
			assert(nimPow(i, 2) == nimMul(i, i));
			ull inv = nimInv(i);
			assert(nimMul(i, inv) == 1);
	}
	return 0;
}
