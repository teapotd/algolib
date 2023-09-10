#include "../../../src/math/fft_online.h"
#include "../testing.hpp"

void deterministic() {
	constexpr int N = 2000;
	vector<Zp> slow(N), fast(N);

	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= i-1; j++) {
			slow[i] += (slow[j] * j) * (slow[i-j] / (i-j));
		}
		slow[i] += 1;
	}

	for (int i = 0; i < N; i++) {
		onlineConv(fast, i,
			[&](int j) { assert(j > 0 && j < i); return fast[j] * j; },
			[&](int j) { assert(j > 0 && j < i); return fast[j] / j; });
		fast[i] += 1;
	}

	for (int i = 0; i < N; i++) {
		assert(slow[i].x == fast[i].x);
	}
}

void fuzz() {
}

void benchmark() {
	constexpr int N = 2e5;
	vector<Zp> dp(N);

	measure("onlineConv N=2e5", 1, [&] {
		for (int i = 0; i < N; i++) {
			onlineConv(dp, i,
				[&](int j) { return dp[j] * j; },
				[&](int j) { return dp[j] * j * j; });
			dp[i] += 1;
		}
	});

	consume(&dp);
}
