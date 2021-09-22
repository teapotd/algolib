#include "../../../src/math/matrix.h"

int main() {
	int n; cin >> n;
	Matrix A(n, Row(n));
	each(row, A) each(e, row) cin >> e.x;
	cout << det(A).x << '\n';
	return 0;
}
