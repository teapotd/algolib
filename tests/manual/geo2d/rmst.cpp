#include "../../../src/geo2d/rmst.h"
#include "../testing.h"

void bench() {
	int n = 100000;
	vector<vec> points(n);
	vector<pair<ll, pii>> G;

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
	vector<vec> points(n);
	each(p, points) cin >> p.x >> p.y;

	vector<pair<ll, pii>> G;
	cout << rmst(points, G) << endl;
	return 0;
}
