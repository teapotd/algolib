#include "../../src/text/suffix_array_linear.h"
#include "../../src/text/kmr.h"
#include "../testing.h"

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	Vi sufsKmr = KMR(str).sufArray();
	Vi sufs = sufArray(str);

	if (sufsKmr != sufs) {
		deb(sufsKmr);
		deb(sufs);
		exit(0);
	}
}

void perfTest() {
	string str(1e6, 'a');
	each(c, str) c = char('a' + r(0, 20));
	sufArray(str);
}

int main() {
	rep(alpha, 1, 10) rep(n, 1, 50) {
		// deb(n, alpha);
		rep(i, 0, 10) {
			test(n, alpha);
		}
	}

	cerr << "OK\n";
	perfTest();
	return 0;
}
