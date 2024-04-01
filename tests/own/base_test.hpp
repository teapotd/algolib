#pragma once

#include "utils.hpp"

void deterministic(); // Deterministic/unit tests entry point.
void fuzz();          // Single fuzzing cycle entry point.
void benchmark();     // Benchmarks entry point.

void runInfiniteFuzzing() {
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	for (long long i = 1;; i++) {
		random_utils::twister.seed(++seed);
		std::cerr << "cycle #" << i << " (seed = " << seed << ")" << std::endl;
		fuzz();
	}
}

int main(int argc, char *argv[]) {
	feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
	std::string mode = (argc < 2 ? "deterministic" : argv[1]);
	if (mode == "deterministic" || mode == "d") {
		deterministic();
		random_utils::twister.seed(1);
		fuzz(); // Run single fuzzing cycle with fixed seed.
	} else if (mode == "fuzz" || mode == "f") {
		runInfiniteFuzzing();
	} else if (mode == "bench" || mode == "b") {
		benchmark();
	} else {
		std::cerr << "Valid test modes: deterministic, fuzz, bench" << std::endl;
		return 1;
	}
	std::cerr << "OK!" << std::endl;
	return 0;
}

using namespace std;
using namespace random_utils;
using namespace utils;
