#pragma once
#include "../template.h"
#include "kmr.h"

// Compute suffix array for KMR-precomputed
// string; time: O(n lg n)
// (note: KMR implicit constructor will convert
// string to KMR and it takes O(n lg^2 n))
Vi sufArray(const KMR& kmr) {
	Vi sufs(sz(kmr.ids.back()));
	iota(all(sufs), 0);
	sort(all(sufs), [&](int l, int r) {
		return kmr.ids.back()[l]<kmr.ids.back()[r];
	});
	return sufs;
}
