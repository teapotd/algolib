#pragma once
#include "../../template.h"

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
// gp_hash_table<K, V> = faster unordered_set

// Anti-anti-hash
const size_t HXOR = mt19937_64(time(0))();
template<class T> struct SafeHash {
	size_t operator()(const T& x) const {
		return hash<T>()(x ^ T(HXOR));
	}
};
