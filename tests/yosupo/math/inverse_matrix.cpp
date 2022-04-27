#include "../../../src/math/matrix.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	Matrix A(n, Row(n));
	each(row, A) each(e, row) cin >> e.x;

	if (!invert(A)) {
		cout << "-1\n";
		return 0;
	}

	each(row, A) {
		each(e, row) cout << e.x << ' ';
		cout << '\n';
	}
	return 0;
}
