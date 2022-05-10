#include "../../../src/math/fft_mod.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	ll n, m; cin >> n >> m;
	vector<ll> a(n), b(m);
	each(k, a) cin >> k;
	each(k, b) cin >> k;
	convolve(a, b);
	each(k, a) cout << k << ' ';
	cout << '\n';
	return 0;
}
