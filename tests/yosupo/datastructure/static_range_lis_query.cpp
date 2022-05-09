#include "../../../src/text/monge.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, q;
	cin >> n >> q;

	Vi seq(n);
	each(p, seq) cin >> p;

	ALIS alis(seq);

	while (q--) {
		int b, e; cin >> b >> e;
		cout << alis(b, e) << '\n';
	}
	return 0;
}
