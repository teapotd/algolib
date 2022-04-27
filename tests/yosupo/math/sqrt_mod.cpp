#include "../../../src/math/modular_sqrt.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int y, p; cin >> y >> p;
		cout << modSqrt(y, p) << '\n';
	}
	return 0;
}
