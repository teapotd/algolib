#pragma once
#include "../template.h"

//!!IGNORE
using ul = unsigned long;
constexpr int BITS = sizeof(ul)*8;

ul untilBit(int i) { return (ul(1) << i) - 1; }
ul sinceBit(int i) { return ul(-1) << i; }

template<size_t N>
struct bitset_plus : bitset<N> {
	// _Find_first() - returns first bit = 1 or N
	// _Find_next(i) - returns first bit = 1
	//                 after i-th bit
	//                 or N if not found

	ul* data() { return (ul*)this; }

	// XOR segment [begin;end) to [dst;end-begin)
	// (segments must not intersect)
	// time: O(n/W), where W is word size
	void xorSegment(int dst, int begin, int end){
	}
};
