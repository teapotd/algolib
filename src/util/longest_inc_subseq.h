#pragma once
#include "../template.h"

// Longest Increasing Subsequence; O(n lg n)
vi lis(const vi& seq) {
	vi dp(sz(seq)+1, INT_MAX);
	vi ind(sz(dp), -1), prv(sz(dp));

	rep(i, 0, sz(seq)) {
		int j = int(lower_bound(1+all(dp), seq[i])
		            - dp.begin());
		prv[i] = ind[j-1];
		dp[j] = seq[ind[j] = i];
	}

	vi ret;
	int i = *--find(1+all(ind), -1);
	while (i != -1) ret.pb(i), i = prv[i];
	reverse(all(ret));
	return ret;
}
