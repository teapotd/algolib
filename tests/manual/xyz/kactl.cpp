#include "../../../src/xyz/kactl.h"

int main() {
	vector<P3> A;
	A.pb(P3(1,2,3));
	A.pb(P3(5,4,3));
	A.pb(P3(-1,-2,-3));
	A.pb(P3(0,0,0));
	hull3d(A);

	vector<vec2i> B;
	B.pb({1,2});
	B.pb({3,4});
	B.pb({5,6});
	delaunay(B, [](int a, int b, int c) { deb(a, b, c); });
	return 0;
}
