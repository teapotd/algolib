#include "../../../src/structures/intset.h"

constexpr int MAX_N = 1e7;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	string s;
	cin >> s;

	IntSet<MAX_N> ds;

	for (int i = 0; i < n; i++) {
		if (s[i] == '1') {
			ds.add(i);
		}
	}

	while (q--) {
		int t, k;
		cin >> t >> k;
		if (t == 0) {
			ds.add(k);
		} else if (t == 1) {
			ds.del(k);
		} else if (t == 2) {
			cout << ds.has(k) << '\n';
		} else if (t == 3) {
			cout << (ds.has(k) ? k : ds.next(k)) << '\n';
		} else if (t == 4) {
			cout << (ds.has(k) ? k : ds.prev(k)) << '\n';
		}
	}

	return 0;
}
