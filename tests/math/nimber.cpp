#include "../../lib/math/nimber.h"
#include "../testing.h"

void perfTest() {
	ull ans = 0;
	NimMult mult = rnd64();

	rep(i, 0, 1<<25) {
		ull a = rnd64();
		ans ^= mult(a);
	}

	cout << ans << endl;
}

int main() {
	initNimMul();

	rep(i, 0, 16) {
		rep(j, 0, 16) {
			cout << setw(6) << nbuf[i][j] << ' ';
		}
		cout << endl;
	}

	cout << endl;

	rep(i, 0, 16) {
		rep(j, 0, 16) {
			NimMult mi = i;
			assert(mi(j) == nimMul(i, j));
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
