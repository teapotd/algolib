#include "../../../src/text/kmr.h"
#include "../testing.h"

void test(int n, int alpha) {
	string str;
	rep(i, 0, n) {
		str.pb(char('a' + r(0, alpha-1)));
	}

	KMR kmr(str);

	rep(b1, 0, n+1) rep(e1, b1, n+1) {
		rep(b2, 0, n+1) rep(e2, b2, n+1) {
			string sub1 = str.substr(b1, e1-b1);
			string sub2 = str.substr(b2, e2-b2);

			int a = strcmp(sub1.c_str(), sub2.c_str());
			int b = kmr.cmp(b1, e1, b2, e2);
			a = (a > 0) - (a < 0);
			//deb(b1, e1, b2, e2, sub1, sub2, a, b);
			assert(a == b);
		}
	}

	Vi sufs = kmr.sufArray();
	rep(i, 1, sz(sufs)) {
		assert(strcmp(&str[sufs[i-1]], &str[sufs[i]]) < 0);
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
