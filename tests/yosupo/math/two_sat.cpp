#include "../../../src/graphs/2sat.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	string tmp;
	int n, m;
	cin >> tmp >> tmp >> n >> m;

	SAT2 sat(n);

	rep(i, 0, m) {
		int a, b, c;
		cin >> a >> b >> c;
		sat.either(a, b);
	}

	if (!sat.solve()) {
		cout << "s UNSATISFIABLE\n";
		return 0;
	}

	cout << "s SATISFIABLE\n";
	cout << "v ";
	rep(i, 1, n+1) {
		cout << (sat[i] ? i : -i) << ' ';
	}
	cout << "0\n";
	return 0;
}
