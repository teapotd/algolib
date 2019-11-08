#pragma once
#include "../template.h"

// Compress integers to range [0;n) while
// preserving their order; time: O(n lg n)
// Returns mapping: compressed -> original
Vi compressVec(vector<int*>& vec) {
	sort(all(vec),
		[](int* l, int* r) { return *l < *r; });
	Vi old;
	each(e, vec) {
		if (old.empty() || old.back() != *e)
			old.pb(*e);
		*e = sz(old)-1;
	}
	return old;
}
