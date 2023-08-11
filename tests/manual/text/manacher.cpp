#include "../../../src/text/manacher.h"
#include "../testing.h"

vi naiveManacherOld(const string& tmp) {
	string str;
	each(c, tmp) {
		str.pb(c);
		str.pb('#');
	}

	vi ret(sz(str));

	rep(i, 0, sz(str)) {
		int k = 1;
		while (i+k < sz(str) && i-k >= 0 && str[i-k] == str[i+k]) {
			k++;
		}

		if (str[i-k+1] == '#') k--;
		ret[i] = k/2 + (i%2 == 0);
	}

	return ret;
}

array<vi, 2> naiveManacher(const string& s) {
	int n = sz(s);
	array<vi, 2> p = {vi(n+1), vi(n)};
	vi old = naiveManacherOld(s);
	rep(i, 0, n) {
		p[0][i+1] = old[i*2+1];
		p[1][i] = old[i*2] - 1;
	}
	return p;
}

void test(const string& str) {
	auto naive = naiveManacher(str);
	auto fast = manacher(str);
	// deb(naive, fast);
	assert(naive == fast);
}

void testRandom(int n, int alpha) {
	string str;
	rep(i, 0, n) str.pb(char('a' + r(0, alpha-1)));
	test(str);
}

void testAll(int n, int alpha) {
	string str(n, 'a');
	bool ok = 1;
	while (ok) {
		test(str);
		ok = 0;
		rep(i, 0, n) {
			if (++str[i] == char('a'+alpha)) {
				str[i] = 'a';
			} else {
				ok = 1;
				break;
			}
		}
	}
}

int main() {
	rep(n, 1, 20) {
		testAll(n, 2);
	}

	while (true) {
		int n = r(21, 100);
		int alpha = r(2, 3);
		testRandom(n, alpha);
	}

	// testRandom(1e6, 1);
	return 0;
}
