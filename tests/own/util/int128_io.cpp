#include "../../../src/util/int128_io.h"
#include "../base_test.hpp"

constexpr __int128 INT128_MIN = numeric_limits<__int128>::min();
constexpr __int128 INT128_MAX = numeric_limits<__int128>::max();

void checkWithLL(const vector<__int128>& elems) {
	ostringstream out, outLL;
	each(e, elems) {
		out << e << ' ';
		outLL << ll(e) << ' ';
	}
	assert(out.str() == outLL.str());
}

void check(const vector<__int128>& elems) {
	ostringstream out;
	each(e, elems) out << e << ' ';
	istringstream in(out.str());
	each(e, elems) {
		__int128 f; in >> f;
		assert(e == f);
	}
}

void deterministic() {
	vector<__int128> elems;

	for (int i = 1; i < int(1e6); i++) {
		elems.pb(i);
		elems.pb(-i);
	}

	checkWithLL(elems);

	for (int i = 0; i < int(1e6); i++) {
		elems.pb(INT128_MIN+i+1);
		elems.pb(INT128_MAX-i);
	}

	check(elems);
}

void fuzz() {
	vector<__int128> elems(1e6);
	each(e, elems) {
		e = (__int128(twister()) << 64) | twister();
	}
	check(elems);
}

void benchmark() {
}
