#pragma once
#include "../template.h"

// Compress integers to range [0;n) while
// preserving their order; time: O(n lg n)
// Returns count n of different numbers
int compressVec(vector<int*>& vec) {
	sort(all(vec), [](int* l, int* r) {
		return *l < *r;
	});
	int last = *vec[0], i = 0;
	each(e, vec) {
		if (*e != last) i++;
		last = *e; *e = i;
	}
	return i+1;
}
