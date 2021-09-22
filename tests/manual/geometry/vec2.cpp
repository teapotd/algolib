#include "../../../src/geometry/vec2.h"
#include "../testing.h"
using namespace rel_ops;

void check(vec2 a, vec2 b) {
		assert((a < b) == (a.angle() < b.angle()));
		assert((a > b) == (a.angle() > b.angle()));
}

int main() {
	rep(i, 0, 1000) {
		vec2 a{rf(-1e9, 1e9), rf(-1e9, 1e9)};
		vec2 b{rf(-1e9, 1e9), rf(-1e9, 1e9)};
		check(a, b);
		check(a, a);
	}
	return 0;
}
