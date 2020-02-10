#include "../../src/math/modular.h"
#include "../../src/math/polynomial_interp.h"
#include "../testing.h"

Zp eval(const vector<Zp>& poly, Zp x) {
	Zp ret = 0, mult = 1;
	each(c, poly) {
		ret += mult*c;
		mult *= x;
	}
	return ret;
}

int main() {
	rep(t, 0, 1000) {
		int n = r(1, 20);
		vector<pair<Zp, Zp>> points(n);

		each(p, points) {
			p.x = r(0, 1e8);
			p.y = r(0, 1e8);
		}

		vector<Zp> poly = polyInterp(points);
		each(p, points) {
			assert(eval(poly, p.x).x == p.y.x);
		}
	}
	return 0;
}
