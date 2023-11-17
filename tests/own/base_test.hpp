#pragma once

#include "utils.hpp"

void deterministic();
void fuzz();
void benchmark();

void runInfiniteFuzzing() {
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	for (long long i = 1;; i++) {
		random_utils::twister.seed(++seed);
		std::cerr << "cycle #" << i << " (seed = " << seed << ")" << std::endl;
		fuzz();
	}
}

extern "C" void __sanitizer_print_stack_trace(int);

int main(int argc, char *argv[]) {
	#if __SANITIZE_ADDRESS__
	signal(6, __sanitizer_print_stack_trace);
	#endif
	std::string mode = (argc < 2 ? "deterministic" : argv[1]);
	if (mode == "deterministic" || mode == "d") {
		deterministic();
		random_utils::twister.seed(1);
		fuzz();
	} else if (mode == "fuzz" || mode == "f") {
		runInfiniteFuzzing();
	} else if (mode == "bench" || mode == "b") {
		benchmark();
	} else {
		std::cerr << "Valid test modes: deterministic, fuzz, bench" << std::endl;
		return 1;
	}
	cout << "OK!" << endl;
	return 0;
}

using namespace std;
using namespace random_utils;
using namespace utils;
