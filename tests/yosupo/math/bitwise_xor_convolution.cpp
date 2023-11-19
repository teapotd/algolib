#define FWHT_XOR
#include "../../../src/math/modular.h"
#include "../../../src/math/fwht.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	ll n; cin >> n;
	n = 1 << n;
	vector<Zp> a(n), b(n);
	each(k, a) cin >> k.x;
	each(k, b) cin >> k.x;
	bitConv(a, b);
	each(k, a) cout << k.x << ' ';
	cout << '\n';
	return 0;
}
