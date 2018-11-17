#pragma once
#include "../template.h"

// Queue with max query on contained elements
struct MaxQueue {
	using T = ll;
	deque<T> Q;

	// Add v to the back; time: amortized O(1)
	void push(T v) {
		while (!Q.empty() && Q.front() < v)
			Q.pop_front();
		Q.push_front(v);
	}

	// Pop from the back (v must be the last one)
	// time: amortized O(1)
	void pop(T v) {
		if (Q.back() == v) Q.pop_back();
	}

	// Get max element value; time: O(1)
	T max() const { return Q.back(); }
};
