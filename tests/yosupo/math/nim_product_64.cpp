#include "../../../src/math/nimber.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	initNimMul();
	int t; cin >> t;
	while (t--) {
		ull a, b; cin >> a >> b;
		cout << nimMul(a, b) << '\n';
	}
	return 0;
}
