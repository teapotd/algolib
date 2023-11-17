#include "../../../src/math/miller_rabin.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		ll n; cin >> n;
		cout << (isPrime(n) ? "Yes\n" : "No\n");
	}
	return 0;
}
