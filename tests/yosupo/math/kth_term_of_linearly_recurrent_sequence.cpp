#include "../../../src/math/linear_rec_fast.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int d;
	ll k;
	cin >> d >> k;

	Poly a(d), c(d);
	each(e, a) cin >> e.x;
	each(e, c) cin >> e.x;

	cout << linearRec(a, c, k).x << '\n';
	return 0;
}
