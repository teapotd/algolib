#include "../../lib/text/suffix_array_linear.h"
#define sufArray sufArrayKmr
#define lcpArray lcpArrayKmr
#include "../../lib/text/suffix_array.h"
#undef sufArray
#undef lcpArray
#include "../testing.h"

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	Vi sufsKmr = sufArrayKmr(KMR(str));
	Vi sufs = sufArray(str);

	if (sufsKmr != sufs) {
		deb(sufsKmr);
		deb(sufs);
		exit(0);
	}
}

int main() {
	rep(alpha, 1, 10) rep(n, 1, 50) {
		deb(n, alpha);
		rep(i, 0, 10) {
			test(n, alpha);
		}
	}
	cerr << "OK\n";
	return 0;
}
