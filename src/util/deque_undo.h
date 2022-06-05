#pragma once
#include "../template.h"

// Deque-like undoing on data structures with
// amortized O(log n) overhead for operations.
// Maintains a deque of objects alongside
// a data structure that contains all of them.
// The data structure only needs to support
// insertions and undoing of last insertion
// using the following interface:
// - insert(...) - insert an object to DS
// - time() - returns current version number
// - rollback(t) - undo all operations after t
// Assumes time() == 0 for empty DS.
struct DequeUndo {
	// Argument for insert(...) method of DS.
	using T = tuple<int, int>;
	DataStructure ds; // Configure DS type here.
	vector<T> elems[2];
	vector<Pii> his = {{0,0}};

	// Push object to front or back of deque,
	// depending on side parameter.
	void push(T val, bool side) {
		elems[side].pb(val);
		doPush(0, side);
	}

	// Pop object from front or back of deque,
	// depending on side parameter.
	void pop(int side) {
		auto &A = elems[side], &B = elems[!side];
		int cnt[2] = {};

		if (A.empty()) {
			assert(!B.empty());
			auto it = B.begin() + sz(B)/2 + 1;
			A.assign(B.begin(), it);
			B.erase(B.begin(), it);
			reverse(all(A));
			his.resize(1);
			cnt[0] = sz(A);
			cnt[1] = sz(B);
		} else {
			do {
				cnt[his.back().y ^ side]++;
				his.pop_back();
			} while (cnt[0]*2 < cnt[1] &&
			         cnt[0] < sz(A));
		}

		cnt[0]--;
		A.pop_back();
		ds.rollback(his.back().x);
		for (int i : {1, 0})
			while (cnt[i]) doPush(--cnt[i], i^side);
	}

	void doPush(int i, bool s) {
		apply([&](auto... x) { ds.insert(x...); },
			elems[s].rbegin()[i]);
		his.pb({ds.time(), s});
	}
};
