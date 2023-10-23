#pragma once

#include <bits/stdc++.h>

namespace random_utils {
	static std::mt19937_64 twister(1337);

	// Random integer between l and r (inclusive).
	template<typename T>
	std::enable_if_t<std::is_integral_v<T>, T> randRange(T l, T r) {
		assert(l <= r);
		std::uniform_int_distribution<T> uniformRand(l, r);
		return uniformRand(twister);
	}

	// Random real number between l and r (inclusive).
	template<typename T>
	std::enable_if_t<std::is_floating_point_v<T>, T> randRange(T l, T r) {
		assert(l <= r);
		std::uniform_real_distribution<T> uniformRand(l, r);
		return uniformRand(twister);
	}

	inline int randInt(int l, int r) {
		return randRange(l, r);
	}

	inline long long randLong(long long l, long long r) {
		return randRange(l, r);
	}

	inline double randDouble(double l, double r) {
		return randRange(l, r);
	}

	inline double randDouble() {
		return randDouble(0, 1);
	}

	inline bool randBool() {
		return twister() % 2;
	}

	// Returns `true` with probability p, `false` with probability 1-p.
	inline bool randBool(double p) {
		std::bernoulli_distribution dist(p);
		return dist(twister);
	}

	// Random number from gamma distribution.
	inline double randGamma(double alpha = 1, double beta = 1) {
		std::gamma_distribution<> dist(alpha, beta);
		return dist(twister);
	}

	// Random number from beta distribution. Can be used to generate biased values.
	// For example, k-th smallest value of n samples from Uniform[0,1] has distribution Beta[k,n+1-k].
	inline double randBeta(double alpha, double beta) {
		double x = randGamma(alpha);
		double y = randGamma(beta);
		return x / (x + y);
	}

	// Random integer between l and r (inclusive) rounded from beta distribution.
	// Can be used to generate biased values.
	// For example, k-th smallest value of n samples from Uniform[0,1] has distribution Beta[k,n+1-k].
	template<typename T>
	std::enable_if_t<std::is_integral_v<T>, T> randBeta(T l, T r, double alpha, double beta) {
		assert(l <= r);
		double x = randBeta(alpha, beta) * double(r - l);
		return std::clamp(l + (T)llround(x), l, r);
	}

	// Random element from given collection.
	template<typename CollectionT>
	typename CollectionT::value_type randElement(const CollectionT& c) {
		assert(!c.empty());
		return c[randInt(0, int(c.size()) - 1)];
	}

	// Random element from initializer list.
	// Example usage: randElement({"aa", "bb", "cc"}).
	template<typename T>
	T randElement(const std::initializer_list<T>& c) {
		return randElement(std::vector<T>(c.begin(), c.end()));
	}

	// Permutes elements in given collection randomly.
	template<typename CollectionT>
	void randShuffle(CollectionT& c) {
		std::shuffle(c.begin(), c.end(), twister);
	}

	// Returns random permutation of {mn, ..., mx}.
	template<typename T>
	std::vector<T> randPermutation(T mn, T mx) {
		assert(mx-mn+1 >= 0);
		std::vector<T> vec(mx - mn + 1);
		std::iota(vec.begin(), vec.end(), mn);
		randShuffle(vec);
		return vec;
	}

	// Fills with K random values (with repetitions) from a range [mn, mx].
	template<typename It, typename T>
	void randWithRepetitions(It begin, It end, T mn, T mx) {
		assert(begin <= end && mn <= mx);
		std::generate(begin, end, std::bind(randRange<T>, mn, mx));
	}

	// Returns K random values (with repetitions) from a range [mn, mx].
	template<typename T>
	std::vector<T> randWithRepetitions(T mn, T mx, int k) {
		assert(k >= 0);
		std::vector<T> values(k);
		randWithRepetitions(values.begin(), values.end(), mn, mx);
		return values;
	}

	// Returns K random values (with repetitions) from a range [mn, mx].
	// Can be used in structured bindings: auto [a, b, c] = randWithRepetitions<3>(1, 10);
	template<size_t k, typename T>
	std::array<T, k> randWithRepetitions(T mn, T mx) {
		std::array<T, k> values;
		randWithRepetitions(values.begin(), values.end(), mn, mx);
		return values;
	}

	// Returns random string with characters from range [mn, mx].
	string randString(char mn, char mx, int k) {
		assert(k >= 0);
		string str(k, '.');
		randWithRepetitions(str.begin(), str.end(), mn, mx);
		return str;
	}

	// Fills with K random values (without repetitions) from a range [mn, mx].
	template<typename It, typename T>
	std::enable_if_t<std::is_integral_v<T>> randDistinct(It begin, It end, T mn, T mx) {
		// Adapted from testlib.h
		assert(begin <= end && mn <= mx);
		int64_t size = int64_t(end - begin);
		int64_t range = int64_t(mx - mn + 1);
		assert(range >= size);

		if (size <= 8) {
			// Faster O(n^2) for very small collections.
			for (It it = begin; it < end; it++) {
				do {
					*it = randRange(mn, mx);
				} while (std::find(begin, it, *it) != it);
			}
		} else if (size*20 < range) {
			std::set<T> vals;
			while (begin < end) {
				T x = randRange(mn, mx);
				if (vals.insert(x).second) {
					*begin++ = x;
				}
			}
		} else {
			assert(range < int(1e9));
			auto p = randPermutation(mn, mx);
			copy(p.begin(), p.begin()+size, begin);
		}
	}

	// Returns K random values (without repetitions) from a range [mn, mx].
	template<typename T>
	std::vector<T> randDistinct(T mn, T mx, int k) {
		std::vector<T> values(k);
		randDistinct(values.begin(), values.end(), mn, mx);
		return values;
	}

	// Returns K random values (without repetitions) from a range [mn, mx].
	// Can be used in structured bindings: auto [a, b, c] = randDistinct<3>(1, 10);
	template<size_t k, typename T>
	std::array<T, k> randDistinct(T mn, T mx) {
		std::array<T, k> values;
		randDistinct(values.begin(), values.end(), mn, mx);
		return values;
	}

	// Returns K random values (without repetitions) out of a specified collection.
	template<typename CollectionT>
	CollectionT randDistinct(const CollectionT& values, int k) {
		assert(k >= 0 && k <= int(values.size()));
		CollectionT samples;
		for (int i : randDistinct(0, int(values.size())-1, k)) {
			samples.push_back(values[i]);
		}
		return values;
	}
};

namespace utils {
	// Consumed CPU time in seconds.
	double cpuTime() {
		return double(clock()) / double(CLOCKS_PER_SEC);
	}

	// Format seconds as s, ms, us or ns.
	std::string formatTime(double time) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(3);
		for (std::string suffix : {"s", "ms", "us"}) {
			if (time >= 0.1) {
				ss << time << suffix;
				return ss.str();
			}
			time *= 1000;
		}
		ss << time << "ns";
		return ss.str();
	}

	// Benchmark given lambda.
	template<class F>
	void measure(std::string name, int rounds, F func) {
		double before = cpuTime();
		for (int i = 0; i < rounds; i++) {
			func();
		}
		double after = cpuTime();
		double perRound = (after-before) / double(rounds);
		std::cerr << name << " : " << formatTime(perRound) << std::endl;
	}

	template<class F>
	void measure(std::string name, F func) {
		measure(name, 1, func);
	}

	// Prevent value from being optimized away.
	template<class T>
	inline void consume(T&& value) {
		asm volatile("" : "+r" (value));
	}

	// Compare two integers.
	template<typename T>
	std::enable_if_t<std::is_integral_v<T>, int> compare(T l, T r) {
		return (l > r) - (l < r);
	}

	// Compare two floating point numbers with epsilon.
	template<typename T>
	std::enable_if_t<std::is_floating_point_v<T>, int> compare(T l, T r) {
		constexpr T eps = 1e-12;
		return (l-r > eps) - (l-r < -eps);
	}

	template<class T>
	bool isEqual(T l, T r) { return compare(l, r) == 0; }

	template<class T>
	bool isLess(T l, T r) { return compare(l, r) < 0; }

	template<class T>
	bool isGreater(T l, T r) { return compare(l, r) > 0; }

	template<class T>
	bool isLeq(T l, T r) { return compare(l, r) <= 0; }

	template<class T>
	bool isGeq(T l, T r) { return compare(l, r) >= 0; }

	template<class CollectionT>
	bool areElementsUnique(const CollectionT& elems) {
		sort(elems.begin(), elems.end());
		return unique(elems.begin(), elems.end()) == elems.end();
	}

	template<class CollectionT>
	bool isSubsequence(const CollectionT& big, const CollectionT& sub) {
		auto it = big.begin();
		size_t i = 0;
		for (auto x : sub) {
			do {
				if (it == big.end()) {
					return false;
				}
			} while (*it++ != x);
		}
		return true;
	}
};

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

int main(int argc, char *argv[]) {
	std::string mode = (argc < 2 ? "deterministic" : argv[1]);
	if (mode == "deterministic") {
		deterministic();
		fuzz();
	} else if (mode == "fuzz") {
		runInfiniteFuzzing();
	} else if (mode == "bench") {
		benchmark();
	} else {
		std::cerr << "Valid test modes: deterministic, fuzz, bench" << std::endl;
		return 1;
	}
	return 0;
}

using namespace std;
using namespace random_utils;
using namespace utils;
