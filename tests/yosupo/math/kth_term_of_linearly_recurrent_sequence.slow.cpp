#include "../../../src/math/linear_rec.h"

int main() {
	int d;
	ll k;
	cin >> d >> k;

	if (d > 5000) {
		cout << "IGNORE-TEST\n";
		return 0;
	}

	Poly a(d), c(d);
	each(e, a) cin >> e;
	each(e, c) cin >> e;

	cout << linearRec(a, c, k) << '\n';
	return 0;
}
