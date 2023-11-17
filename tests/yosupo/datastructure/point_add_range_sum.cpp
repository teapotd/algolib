#include "../../../src/structures/fenwick_tree.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	Fenwick tree(n);

	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		tree.modify(i, a);
	}

	while (q--) {
		int t, a, b;
		cin >> t >> a >> b;
		if (t == 0) {
			tree.modify(a, b);
		} else {
			auto ans = tree.query(b) - tree.query(a);
			cout << ans << '\n';
		}
	}

	return 0;
}
