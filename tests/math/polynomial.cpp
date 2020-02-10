#include "../../src/math/polynomial.h"
#include "../testing.h"

bool operator==(Zp l, Zp r) { return l.x == r.x; }
bool operator!=(Zp l, Zp r) { return l.x != r.x; }

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
	P = Poly{1,1,1,1,1};
	derivate(P);
	assert((P == Poly{1,2,3,4}));
	integrate(P);
	assert((P == Poly{0,1,1,1,1}));

	return 0;
}
