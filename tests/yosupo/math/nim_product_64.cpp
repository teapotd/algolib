#include "../../../src/math/nimber.h"

int main() {
	initNimMul();
	int t; cin >> t;
	while (t--) {
		ull a, b; cin >> a >> b;
		cout << nimMul(a, b) << '\n';
	}
	return 0;
}
