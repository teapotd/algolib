#include "../../../src/graphs/matching_boski.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int l, r, m;
	cin >> l >> r >> m;

	vector<vi> G(r);

	rep(i, 0, m) {
		int a, b; cin >> a >> b;
		G[b].pb(a);
	}

	Matching match(l);
	int ans = 0;
	each(vec, G) ans += match.add(vec);

	cout << ans << '\n';

	rep(v, 0, l) {
		if (match[v] != -1) {
			cout << v << ' ' << match[v] << '\n';
		}
	}
	return 0;
}
