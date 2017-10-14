#pragma once

#include <iostream>
#include <cstdint>
#include <random>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;

std::mt19937 rnd(time(0));

int64_t r(int64_t l, int64_t r) {
	return (l + (rnd() % (r-l+1)));
}

double rf(double l, double r) {
	double tmp = ((double)rnd() - rnd.min()) / (rnd.max() - rnd.min());
	return (l + (tmp * (r-l)));
}

std::vector<int64_t> perm(int64_t l, int64_t r) {
	std::vector<int64_t> ret;
	for (int i = l; i <= r; i++) {
		ret.push_back(i);
	}

	std::random_shuffle(ret.begin(), ret.end());
	return ret;
}

Time   now()             { return Clock::now(); }
double since(Time begin) { return (now() - begin).count(); }
