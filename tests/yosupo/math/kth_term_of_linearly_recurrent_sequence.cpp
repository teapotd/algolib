#include "../../../src/math/linear_rec_fast.h"

int main() {
	int d;
	ll k;
	cin >> d >> k;

	Poly a(d), c(d);
	each(e, a) cin >> e.x;
	each(e, c) cin >> e.x;

	cout << linearRec(a, c, k).x << '\n';
	return 0;
}

// #include "../../../src/math/linear_rec.h"

// int main() {
// 	int d;
// 	ll k;
// 	cin >> d >> k;

// 	Poly a(d), c(d);
// 	each(e, a) cin >> e;
// 	each(e, c) cin >> e;

// 	if (d > 5000) {
// 		cout << "nope\n";
// 		return 0;
// 	}

// 	cout << linearRec(a, c, k) << '\n';
// 	return 0;
// }
