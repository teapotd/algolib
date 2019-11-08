#pragma once
#include "../template.h"

// Undocumented std::bitset features:
// - _Find_first() - returns first bit = 1 or N
// - _Find_next(i) - returns first bit = 1
//                   after i-th bit
//                   or N if not found

// Bitwise operations for vector<bool>
// UNTESTED

#define OP(x) vector<bool>& operator x##=(    \
		vector<bool>& l, const vector<bool>& r) { \
	assert(sz(l) == sz(r));                     \
	auto a = l.begin(); auto b = r.begin();     \
	while (a<l.end()) *a._M_p++ x##= *b._M_p++; \
	return l; }
OP(&)OP(|)OP(^)
