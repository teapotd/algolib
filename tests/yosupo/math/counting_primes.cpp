#include "../../../src/math/pi_large.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	ll n; cin >> n;
	initPi();
	cout << pi(n) << '\n';
	return 0;
}
