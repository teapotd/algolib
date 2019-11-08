#pragma once
#include "../template.h"

// Range Minimum Query; space: O(n lg n)
struct RMQ {
	using T = int;
	static constexpr T ID = INT_MAX;
	T f(T a, T b)  { return min(a, b); }

	vector<vector<T>> s;

	// Initialize RMQ structure; time: O(n lg n)
	RMQ(const vector<T>& vec = {}) {
		s = {vec};
		for (int h = 1; h <= sz(vec); h *= 2) {
			s.emplace_back();
			auto& prev = s[sz(s)-2];
			rep(i, 0, sz(vec)-h*2+1)
				s.back().pb(f(prev[i], prev[i+h]));
		}
	}

	// Query f(s[b], ... ,s[e-1]); time: O(1)
	T query(int b, int e) {
		if (b >= e) return ID;
		int k = 31 - __builtin_clz(e-b);
		return f(s[k][b], s[k][e - (1<<k)]);
	}
};
