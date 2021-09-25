#include "../../../src/graphs/bipartite_edge_coloring.h"

int main() {
	int l, r, m; cin >> l >> r >> m;
	vector<Pii> edges(m);
	each(e, edges) cin >> e.x >> e.y;

	if (l > 10000 || r > 10000 || m > 10000) {
		cout << "nope\n";
		return 0;
	}

	int ans;
	Vi colors;
	ans = colorEdges(edges, max(l, r), colors);

	cout << ans << '\n';
	each(c, colors) cout << c << ' ';
	cout << '\n';
	return 0;
}
