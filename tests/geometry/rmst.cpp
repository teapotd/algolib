#include "../../lib/geometry/rmst.h"
#include "../testing.h"

int main() {
	int n; cin >> n;
	G.resize(n);
	each(v, G) cin >> v.point.x >> v.point.y;

	cout << rmst() << endl;
	return 0;
}
