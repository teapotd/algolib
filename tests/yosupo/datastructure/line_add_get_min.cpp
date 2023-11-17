#include "../../../src/structures/hull_online.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	Hull hull;

	while (n--) {
		ll a, b;
		cin >> a >> b;
		hull.insert(-a, -b);
	}

	while (q--) {
		ll t, a, b;
		cin >> t >> a;
		if (t == 0) {
			cin >> b;
			hull.insert(-a, -b);
		} else {
			cout << -hull.query(a) << '\n';
		}
	}

	return 0;
}
