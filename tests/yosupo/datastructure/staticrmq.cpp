#include "../../../src/structures/rmq.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	vi seq(n);
	each(p, seq) cin >> p;

	RMQ rmq(seq);

	while (q--) {
		int b, e;
		cin >> b >> e;
		cout << rmq.query(b, e) << '\n';
	}

	return 0;
}
