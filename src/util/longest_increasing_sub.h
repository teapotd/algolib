#pragma once
#include "../template.h"

// Longest Increasing Subsequence; O(n lg n)
int lis(const Vi& seq) {
	Vi dp(sz(seq), INT_MAX);
	each(c, seq) *lower_bound(all(dp), c) = c;
	return int(lower_bound(all(dp), INT_MAX)
	           - dp.begin());
}
