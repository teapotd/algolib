#include "../../../src/math/modular_sqrt.h"

int main() {
	int t; cin >> t;
	while (t--) {
		int y, p; cin >> y >> p;
		cout << modSqrt(y, p) << '\n';
	}
	return 0;
}
