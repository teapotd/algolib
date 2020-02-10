#include "../../src/math/polynomial.h"
#include "../testing.h"

bool operator==(Zp l, Zp r) { return l.x == r.x; }
bool operator!=(Zp l, Zp r) { return l.x != r.x; }

void testInvert() {
	rep(t, 0, 100) {
		int n = r(1, 500);
		Poly P(n);
		each(k, P) k = r(1, MOD-1);

		int k = r(1, 1000);
		Poly Q = invert(P, k);

		Poly R = P*Q;
		R.resize(k);
		norm(R);

		assert((R == Poly{1}));
	}
}

void testDivMod() {
	rep(t, 0, 100) {
		int n = r(1, 500);
		int m = r(1, 500);

		Poly P(n), Q(m);
		each(k, P) k = r(1, MOD-1);
		each(k, Q) k = r(1, MOD-1);

		Poly div = P/Q, rem = P%Q;

		assert(sz(div) <= sz(P));
		assert(sz(rem) < sz(Q));
		assert(div*Q + rem == P);
	}
}

int main() {
	// +, -, *, eval, norm
	Poly P = {1,2,3,0,0};
	norm(P);
	assert((P == Poly{1,2,3}));

	Poly Q = P + Poly{0,2,5,2};
	assert((Q == Poly{1,4,8,2}));

	Poly R = Poly{1,4,3,0};
	R -= P;
	assert((R == Poly{0,2}));

	assert(eval(P, 2) == 1+2*2+4*3);

	Poly S = Poly{1,2,3} * Poly{2,5};
	assert((S == Poly{2,4+5,6+10,15}));

	// Derivate, integrate
	P = derivate({1,1,1,1,1});
	assert((P == Poly{1,2,3,4}));
	assert((integrate(P) == Poly{0,1,1,1,1}));

	testInvert();

	P = Poly{8,20,12} / Poly{1,2};
	assert((P == Poly{7, 6}));

	testDivMod();

	return 0;
}
