#include "../../../src/math/fast_mod.h"
#include "../base_test.hpp"

void deterministic() {
}

void fuzz() {
	rep(i, 0, 20'000'000) {
		ull a = randRange<ull>(0, 1e18);
		ull b = randRange<ull>(1, 1e18);
		ull got = FastMod(b)(a);
		assert(got == a%b || got == a%b+b);
	}
}

void benchmark() {
}
