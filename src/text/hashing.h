#pragma once
#include "../template.h"

//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Hashing.h

using ull = uint64_t;

// Arithmetic mod 2^64-1.
// Around 2x slower than mod 2^64.
struct Hash {
	ull x;
	constexpr Hash(ull y = 0) : x(y) {}
	Hash operator+(Hash r) {
		return x + r.x + (x + r.x < x);
	}
	Hash operator-(Hash r) {
		return *this + ~r.x;
	}
	Hash operator*(Hash r) {
		auto m = __uint128_t(x) * r.x;
		return Hash(ull(m)) + ull(m>>64);
	}
	auto get() const { return x + !~x; }
	bool operator==(Hash r) const {
		return get() == r.get();
	}
	bool operator<(Hash r) const {
		return get() < r.get();
	}
	void print() { cerr << x; }
};

// Base for hashing (prime, big order).
constexpr Hash C = ll(1e11-981);

Hash powC(int n) { // C^n
	static vector<Hash> vec = {1};
	while (sz(vec) <= n) vec.pb(vec.back() * C);
	return vec[n];
}

// Precompute prefix hashes for a string.
struct HashInterval : vector<Hash> {
	HashInterval(auto& s) {
		pb(0);
		rep(i, 0, sz(s)) pb(at(i)*C + s[i]);
	}
	// Get hash of interval [b;e)
	Hash operator()(int b, int e) {
		return at(e) - at(b) * powC(e-b);
	}
};
