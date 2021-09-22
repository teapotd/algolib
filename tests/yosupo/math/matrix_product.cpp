#include "../../../src/math/matrix.h"

int main() {
	int n, m, k; cin >> n >> m >> k;
	Matrix A(n, Row(m)), B(m, Row(k));
	each(row, A) each(e, row) cin >> e.x;
	each(row, B) each(e, row) cin >> e.x;

	each(row, A*B) {
		each(e, row) cout << e.x << ' ';
		cout << '\n';
	}
	return 0;
}
