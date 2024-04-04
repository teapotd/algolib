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

	vec3 randVecFromCube(sc b, sc e) {
		return {randCoord(b, e), randCoord(b, e), randCoord(b, e)};
	}

	vec3 randVecFromBall(double minR, double maxR) {
		normal_distribution<double> dist;
		double x = dist(twister), y = dist(twister), z = dist(twister);
		double s = cbrt(randDouble(minR*minR*minR, maxR*maxR*maxR)) / hypot(x, y, z);
		return {sc(x*s), sc(y*s), sc(z*s)};
	}

	vector<vec3> randVecsFromCube(int n, sc minR, sc maxR) {
		vector<vec3> elems(n);
		each(v, elems) v = randVecFromCube(minR, maxR);
		return elems;
	}

	vector<vec3> randVecsFromBall(int n, double minR, double maxR) {
		vector<vec3> elems(n);
		each(v, elems) v = randVecFromBall(minR, maxR);
		return elems;
	}
};

namespace utils {
	bool equalWithEps(vec3 a, vec3 b) {
		return equalWithEps(a.x, b.x) && equalWithEps(a.y, b.y) && equalWithEps(a.z, b.z);
	}
};
