#include "../../../src/math/polynomial.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<Zp> f(n);
	each(e, f) cin >> e.x;
	if (sqrt(f, n)) {
		each(e, f) cout << e.x << ' ';
		cout << '\n';
	} else {
		cout << "-1\n";
	}
	return 0;
}
