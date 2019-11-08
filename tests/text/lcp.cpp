#include "../../src/text/suffix_array_linear.h"
#include "../../src/text/lcp.h"
#include "../testing.h"

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	Vi sufs = sufArray(str);
	Vi lcp = lcpArray(str, sufs);

	rep(i, 0, sz(lcp)) {
		int a = sufs[i], b = sufs[i+1], c = lcp[i];

		rep(j, 0, c) {
			assert(str[a+j] == str[b+j]);
		}

		if (a+c < n && b+c < n) {
			assert(str[a+c] != str[b+c]);
		}
	}
}

int main() {
	rep(alpha, 1, 10) rep(n, 1, 20) {
		deb(n, alpha);
		rep(i, 0, 10) {
			test(n, alpha);
		}
	}
	return 0;
}
