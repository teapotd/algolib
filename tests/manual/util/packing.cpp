#include "../../../src/util/packing.h"
#include "../../../src/template.h"
#include "../testing.h"

void testPacking(const vector<ll>& values, int bits) {
	Writer writer;
	each(v, values) {
		writer.ints(v, bits);
	}
	writer.done();

	string packed = writer.buf;
	for (char c : packed) {
		assert(c >= '#' && c <= '}');
	}

	Reader reader(packed.c_str());
	vector<ll> recovered(values.size());
	each(v, recovered) {
		v = reader.ints(bits);
	}

	deb(packed, recovered);
	assert(values == recovered);
}

int main() {
	while (true) {
		int len = r(0, 10);
		int bits = r(1, 64);
		ll mn = ll(-(1ull << (bits-1)) + 1);
		ll mx = ll((1ull << (bits-1)) - 1);

		vector<ll> values(len);
		each(v, values) {
			v = rl(mn, mx);
		}
		deb(len, bits, values);
		testPacking(values, bits);
	}
	return 0;
}
