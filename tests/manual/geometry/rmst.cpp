#include "../../../src/geometry/rmst.h"
#include "../testing.h"

void bench() {
	int n = 100000;
	vector<Pii> points(n);
	vector<vector<Pii>> G;

	each(p, points) {
		p.x = r(-1e8, 1e8);
		p.y = r(-1e8, 1e8);
	}

	auto before = now();
	rmst(points, G);
	cout << since(before) << "ms" << endl;
}

int main() {
	int n; cin >> n;
	vector<Pii> points(n);
	each(p, points) cin >> p.x >> p.y;

	vector<vector<Pii>> G;
	cout << rmst(points, G) << endl;
	return 0;
}
