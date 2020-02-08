#include "../../src/math/matrix.h"
#include "../testing.h"

int main() {
	Matrix a = {
		{1,2,3},
		{3,4,5},
	};

	Matrix b = {
		{5,10,0},
		{100,200,300},
	};

	Matrix c = {
		{5,10,0},
		{100,200,300},
		{0,0,0},
	};

	deb(a);
	deb(b);
	deb(a+b);
	deb(a*c);
	deb(pow(c, 0));
	deb(pow(c, 3));

	return 0;
}
