#include "../../../src/math/subset_sum_mod.h"
#include "../testing.h"

// Uniformly random sequence of elements of length `count` from range [0;mod-1].
template<typename Rng>
vector<int> random_testcase(Rng rng, int count, int mod) {
	vector<int> elements(count);
	for (int& x : elements) {
		x = uniform_int_distribution<>(0, mod-1)(rng);
	}
	return elements;
}

// Selects uniformly random element x from range [0;mod-1],
// and then returns uniformly random sequence of elements from the set {x, ..., 2sqrt(mod)*x}.
template<typename Rng>
vector<int> random_arith_testcase(Rng rng, int count, int mod) {
	vector<int> elements(count);
	int step, limit = max(int(sqrt(mod*2)), 1);
	do {
		step = uniform_int_distribution<>(1, mod)(rng);
	} while (gcd(step, mod) != 1);
	for (int& x : elements) {
		int64_t k = uniform_int_distribution<>(1, limit)(rng);
		x = int(k*step % mod);
	}
	return elements;
}

// Given attainable subset sums, compute attainable subset sums after adding `x`.
vector<bool> add_element_naive(const vector<bool>& input, int x) {
	int mod = int(input.size());
	auto output = input;
	for (int i = 0; i < mod; i++) {
		if (input[i]) {
			output[(i+x) % mod] = true;
		}
	}
	return output;
}

void check(const vector<int>& counts, const vector<bool>& expected) {
	auto output = subsetSumMod(counts);

	for (int i = 0; i < sz(counts); i++) {
		if (output[i] == -1) {
			assert(!expected[i]);
			continue;
		}

		assert(expected[i]);
		auto subset = recoverSubset(output, i);
		auto tmp = counts;
		int sum = 0;

		each(e, subset) {
			assert(tmp[e] > 0);
			tmp[e]--;
			sum = (sum+e) % sz(counts);
		}

		assert(sum == i);
	}
}

// Test for all prefixes of given element sequence.
void test_incremental(const vector<int>& elements, int mod) {
	vector<int> counts(mod);
	vector<bool> expected(mod);
	expected[0] = true;
	for (int x : elements) {
		expected = add_element_naive(expected, x);
		counts[x]++;
		check(counts, expected);
	}
}

// Test on a random testcase.
template<typename Rng>
void fuzz_single(Rng& rng, int max_elements, int max_modulo) {
	int mod = std::uniform_int_distribution<>(1, max_modulo)(rng);
	std::vector<int> elems;
	if (rng() % 2 == 0) {
		elems = random_testcase(rng, max_elements, mod);
	} else {
		elems = random_arith_testcase(rng, max_elements, mod);
	}
	test_incremental(elems, mod);
}

// Test on random testcases indefinitely.
void fuzz(int max_elements, int max_modulo, int thread_count) {
	std::atomic_int64_t total_passed = 0;

	for (int t = 0; t < thread_count; t++) {
		std::thread([&]() {
			std::mt19937_64 rng(std::random_device{}());
			for (uint64_t i = 1;; i++) {
				fuzz_single(rng, max_elements, max_modulo);
				if (i % 32 == 0) {
					total_passed += 32;
				}
			}
		}).detach();
	}

	while (true) {
		std::this_thread::sleep_for(1000ms);
		std::cout << "tested " << total_passed << " instances..." << std::endl;
	}
}

int main() {
	fuzz(100, 100, 4);
	return 0;
}
