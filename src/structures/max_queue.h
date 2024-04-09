#pragma once
#include "../template.h"
//!!EXCLUDE-FILE

// Queue with max query on contained elements
struct MaxQueue {
	using T = int;
	deque<T> Q, M;

	// Add v to the back; time: amortized O(1)
	void push(T v) {
		while (!M.empty() && M.back() < v)
			M.pop_back();
		M.pb(v); Q.pb(v);
	}

	// Pop from the front; time: O(1)
	void pop() {
		if (M.front() == Q.front()) M.pop_front();
		Q.pop_front();
	}

	// Get max element value; time: O(1)
	T max() const { return M.front(); }
};
