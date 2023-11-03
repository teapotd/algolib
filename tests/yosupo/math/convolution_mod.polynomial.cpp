#include "../../../src/math/polynomial.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	ll n, m; cin >> n >> m;
	Poly a(n), b(m);
	each(k, a) cin >> k.x;
	each(k, b) cin >> k.x;
	a *= b;
	a.resize(n+m-1);
	each(k, a) cout << k.x << ' ';
	cout << '\n';
	return 0;
}
