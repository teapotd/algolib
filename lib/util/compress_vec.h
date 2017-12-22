#pragma once
#include "../template.h"

// Compress values of vector to [0;n) while preserving order
// Time complexity: O(n lg n)

int compressVec(vector<int*>& vec) {
	sort(all(vec), [](int* l, int* r) { return *l < *r; });
	int last = *vec[0], i = 0;
	each(e, vec) {
		if (*e != last) i++;
		last = *e; *e = i;
	}
	return i+1;
}
