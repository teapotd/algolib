#pragma once

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;

std::mt19937 rnd(uint32_t(time(0)));
// std::mt19937 rnd(0);

int r(int l, int r) {
	return (l + (rnd() % (r-l+1)));
}

int64_t rl(int64_t l, int64_t r) {
	return (l + (rnd() % (r-l+1)));
}

double rf(double l, double r) {
	double tmp = ((double)rnd() - rnd.min()) / (rnd.max() - rnd.min());
	return (l + (tmp * (r-l)));
}

std::vector<int64_t> perm(int64_t l, int64_t r) {
	std::vector<int64_t> ret;
	for (int64_t i = l; i <= r; i++) {
		ret.push_back(i);
	}

	std::random_shuffle(ret.begin(), ret.end());
	return ret;
}

Time now() { return Clock::now(); }

int since(Time begin) {
	return int(std::chrono::duration_cast<std::chrono::milliseconds>(now() - begin).count());
}

template<class T>
void generateTree(std::vector<T>& verts) {
	auto shuf = perm(0, int(verts.size())-1);

	for (int i = 1; i < int(verts.size()); i++) {
		int e = r(0, i-1);
		verts[shuf[i]].edges.push_back(int(shuf[e]));
		verts[shuf[e]].edges.push_back(int(shuf[i]));
	}
}
