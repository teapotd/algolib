#include "../../../src/graphs/edge_color_bipart.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int l, r, m; cin >> l >> r >> m;
	vector<pii> edges(m);
	each(e, edges) cin >> e.x >> e.y;

	if (l > 10000 || r > 10000 || m > 10000) {
		cout << "IGNORE-TEST";
		return 0;
	}

	int ans;
	vi colors;
	ans = colorEdges(edges, max(l, r), colors);

	cout << ans << '\n';
	each(c, colors) cout << c << ' ';
	cout << '\n';
	return 0;
}
