#pragma once
#include "../template.h"

// Utilities for packing precomputed tables.
// Encodes 13 bits using two characters.

// Example usage:
//   Writer out;
//   out.ints(-123, 8);
//   out.done();
//   cout << out.buf;
struct Writer {
	string buf;
	int cur = 0, has = 0;

	void done() {
		buf.pb(char(cur%91 + 35));
		buf.pb(char(cur/91 + 35));
		cur = has = 0;
	}

	// Write unsigned b-bit integer.
	void intu(uint64_t v, int b) {
		assert(b == 64 || v < (1ull<<b));
		while (b--) {
			cur |= (v & 1) << has;
			if (++has == 13) done();
			v >>= 1;
		}
	}

	// Write signed b-bit integer (sign included)
	void ints(ll v, int b) {
		intu(v < 0 ? -v*2+1 : v*2, b);
	}
};

// Example usage:
//   Reader in("packed_data");
//   int firstValue = in.ints(8);
struct Reader {
	const char *buf;
	ll cur = 0;

	Reader(const char *s) : buf(s) {}

	// Read unsigned b-bit integer.
	uint64_t intu(int b) {
		uint64_t n = 0;
		rep(i, 0, b) {
			if (cur < 2) {
				cur = *buf++ + 4972;
				cur += *buf++ * 91;
			}
			n |= (cur & 1) << i;
			cur >>= 1;
		}
		return n;
	}

	// Read signed b-bit integer (sign included).
	ll ints(int b) {
		auto v = intu(b);
		return (v%2 ? -1 : 1) * ll(v/2);
	}
};
