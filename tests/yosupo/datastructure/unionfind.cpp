#include "../../../src/structures/find_union.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	FAU dsu(n);

	while (q--) {
		int t, a, b;
		cin >> t >> a >> b;
		if (t == 0) {
			dsu.join(a, b);
		} else {
			bool ans = (dsu.find(a) == dsu.find(b));
			cout << ans << '\n';
		}
	}

	return 0;
}
