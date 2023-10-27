#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

// Tuple of residues for multiple constant modulus.
template<int... Mods>
struct MultiZp;

template<>
struct MultiZp<> {
	constexpr MultiZp() {}
	constexpr MultiZp(int) {}
	constexpr MultiZp& operator+=(const MultiZp&) { return *this; }
	constexpr MultiZp& operator-=(const MultiZp&) { return *this; }
	constexpr MultiZp& operator*=(const MultiZp&) { return *this; }
	constexpr MultiZp operator+(const MultiZp&) const { return {}; }
	constexpr MultiZp operator-(const MultiZp&) const { return {}; }
	constexpr MultiZp operator*(const MultiZp&) const { return {}; }
	constexpr bool operator==(const MultiZp&) const { return true; }
	constexpr bool operator!=(const MultiZp&) const { return false; }
};

template<int Mod, int... OtherMods>
struct MultiZp<Mod, OtherMods...> : private MultiZp<OtherMods...> {
	constexpr MultiZp() : value(0) {}

	constexpr MultiZp(int x) : MultiZp<OtherMods...>(x), value(x % Mod) {
		if (x < 0) {
			x += Mod;
		}
	}

	constexpr MultiZp& operator+=(const MultiZp& r) {
		base() += r.base();
		value += r.value;
		if (value >= Mod) {
			value -= Mod;
		}
		return *this;
	}

	constexpr MultiZp& operator-=(const MultiZp& r) {
		base() -= r.base();
		value -= r.value;
		if (value < 0) {
			value += Mod;
		}
		return *this;
	}

	constexpr MultiZp& operator*=(const MultiZp& r) {
		base() *= r.base();
		value = int(int64_t(value) * r.value % Mod);
		return *this;
	}

	constexpr MultiZp operator+(MultiZp r) const {
		r += *this;
		return r;
	}

	constexpr MultiZp operator-(MultiZp r) const {
		r -= *this;
		return r;
	}

	constexpr MultiZp operator*(MultiZp r) const {
		r *= *this;
		return r;
	}

	constexpr bool operator==(const MultiZp& r) const {
		return base() == r.base() && value == r.value;
	}

	constexpr bool operator!=(const MultiZp& r) const {
		return base() != r.base() || value != r.value;
	}

	const MultiZp<OtherMods...>& base() const { return *this; }
	MultiZp<OtherMods...>& base() { return *this; }

	int value;
};

// Rolling hash for constant root and multiple constant modulus.
template<int Root, int... Mods>
struct RollingHash {
	using Ring = MultiZp<Mods...>;

	constexpr RollingHash() : size(0) {}
	constexpr RollingHash(int v) : value(v), size(1) {}
	constexpr RollingHash(Ring v) : value(v), size(1) {}
	constexpr RollingHash(Ring v, int s) : value(v), size(s) {}

	constexpr bool operator==(const RollingHash& r) const {
		return value == r.value && size == r.size;
	}

	constexpr bool operator!=(const RollingHash& r) const {
		return value != r.value || size != r.size;
	}

	// Get power of root.
	static Ring multiplier(int n) {
		static std::vector<Ring> mult = { 1, Root };
		while (int(mult.size()) <= n) {
			mult.push_back(mult.back() * mult[1]);
		}
		return mult[n];
	}

	// Combine hashes of two strings.
	RollingHash cat(const RollingHash& rhs) {
		return { value + rhs.value * multiplier(size), size + rhs.size };
	}

	// Get hash of string filled with ones.
	static RollingHash ones(int n) {
		static std::vector<RollingHash> ones = { {}, 1 };
		while (int(ones.size()) <= n) {
			ones.push_back(ones.back().cat(ones[1]));
		}
		return ones[n];
	}

	// Get hash of string with all characters increased by `n`.
	RollingHash offset(int n) {
		return { value + ones(size).value * n, size };
	}

	void print() {
		std::cerr << '(' << value.value << ',' << size << ')';
	}

	Ring value;
	int size;
};
