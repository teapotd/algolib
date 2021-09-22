#include "../../../src/math/fwht.h"
#include "../testing.h"

vector<ll> naiveXorConv(vector<ll> A, vector<ll> B) {
	vector<ll> ret(sz(A));
	rep(i, 0, sz(A)) rep(j, 0, sz(A)) ret[i^j] += A[i]*B[j];
	return ret;
}

vector<ll> naiveOrConv(vector<ll> A, vector<ll> B) {
	vector<ll> ret(sz(A));
	rep(i, 0, sz(A)) rep(j, 0, sz(A)) ret[i|j] += A[i]*B[j];
	return ret;
}

vector<ll> naiveAndConv(vector<ll> A, vector<ll> B) {
	vector<ll> ret(sz(A));
	rep(i, 0, sz(A)) rep(j, 0, sz(A)) ret[i&j] += A[i]*B[j];
	return ret;
}

template<class F, class G>
void test(F fast, G naive) {
	rep(i, 0, 100) {
		int p = r(0, 10);
		vector<ll> A(1<<p), B(1<<p);
		each(k, A) k = r(-10000, 10000);
		each(k, B) k = r(-10000, 10000);

		vector<ll> expected = naive(A, B);
		fast(A, B);

		if (A != expected) {
			deb(A);
			deb(expected);
			exit(0);
		}
	}
}

int main() {
	test(bitConv<ll>, naiveXorConv);
	// test(bitConv<ll>, naiveAndConv);
	// test(bitConv<ll>, naiveOrConv);
	return 0;
}
