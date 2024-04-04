#pragma once
#include "../base_test.hpp"

#if FLOATING_POINT_GEOMETRY
constexpr double U = 0.1;
#else
constexpr ll U = 1;
#endif

namespace random_utils {
	sc randCoord(sc b, sc e) {
		return randRange(b, e);
	}

	vec randVecFromSquare(sc b, sc e) {
		return {randCoord(b, e), randCoord(b, e)};
	}

	vec randVecFromDisk(double minR, double maxR) {
		double r = sqrt(randDouble(minR*minR, maxR*maxR));
		double a = randDouble(0, M_PI*2);
		double x = r * cos(a), y = r * sin(a);
		return {sc(x), sc(y)};
	}

	vector<vec> randVecsFromSquare(int n, sc minR, sc maxR) {
		vector<vec> elems(n);
		each(v, elems) v = randVecFromSquare(minR, maxR);
		return elems;
	}

	vector<vec> randVecsFromDisk(int n, double minR, double maxR) {
		vector<vec> elems(n);
		each(v, elems) v = randVecFromDisk(minR, maxR);
		return elems;
	}
};

namespace utils {
	bool equalWithEps(vec a, vec b) {
		return equalWithEps(a.x, b.x) && equalWithEps(a.y, b.y);
	}
};
