#include "../../../src/text/hashing.h"
#include "../testing.hpp"

bool isNice(Hash x) {
	if (gcd(x.get(), UINT64_MAX) != 1) return false;
	Hash cur = x;
	for (ll i = 0; i < ll(1e9); i++) {
		if (cur.get() < ll(1e9)) {
			return false;
		}
		cur = cur * x;
	}
	return true;
}

void deterministic() {
	assert(isNice(C));
}

void fuzz() {
	rep(times, 0, 10000) {
		int n = randInt(1, 1000);
		string t, s = randString('a', 'z', n);
		do {
			t = randString('a', 'z', n);
		} while (s == t);
		string input = s+t+s;
		HashInterval H(input);
		assert(H(0, n).get() != H(n, n*2).get());
		assert(H(0, n).get() == H(n*2, n*3).get());
	}
}

void benchmark() {
}
