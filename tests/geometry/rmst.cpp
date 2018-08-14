#include "../../lib/geometry/rmst.h"
#include "../testing.h"

void bench() {
	int n = 100000;
	G.resize(n);

	each(v, G) {
		v.point.x = r(-1e8, 1e8);
		v.point.y = r(-1e8, 1e8);
	}

	auto before = now();
	rmst();
	cout << since(before) << "ms" << endl;
}

int main() {
	int n; cin >> n;
	G.resize(n);
	each(v, G) cin >> v.point.x >> v.point.y;

	cout << rmst() << endl;
	return 0;
}
