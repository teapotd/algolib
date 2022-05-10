#include "../../../src/math/pollard_rho.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		ll a; cin >> a;
		vector<ll> ans;
		each(f, factorize(a)) {
			rep(i, 0, f.y) ans.pb(f.x);
		}
		cout << sz(ans) << ' ';
		each(p, ans) cout << p << ' ';
		cout << '\n';
	}
	return 0;
}
