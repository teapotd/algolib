#include "../../../src/graphs/directed_mst.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	vector<Edge> edges(m);
	each(e, edges) cin >> e.a >> e.b >> e.w;

	Vi par;
	cout << dmst(edges, n, s, par) << '\n';
	each(i, par) cout << (i != -1 ? i : s) << ' ';
	cout << '\n';
	return 0;
}
