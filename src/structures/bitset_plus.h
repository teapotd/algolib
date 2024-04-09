#pragma once
#include "../template.h"

// Bitwise operations for vector<bool> UNTESTED

#define OP(x) vector<bool>& operator x##=(    \
		vector<bool>& l, const vector<bool>& r) { \
	assert(sz(l) == sz(r));                     \
	auto a = l.begin(); auto b = r.begin();     \
	while (a<l.end()) *a._M_p++ x##= *b._M_p++; \
	return l; }
OP(&)OP(|)OP(^)
