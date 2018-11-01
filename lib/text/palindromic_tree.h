#pragma once
#include "../template.h"

constexpr int ALPHA = 26; // Set alphabet size

// Tree of all palindromes in string,
// constructed online by appending letters.
// space: O(n*ALPHA); time: O(n)
// Code marked with [EXT] is extension for
// calculating minimal palindrome partition
// in O(n lg n). Can also be modified for
// similar dynamic programmings.
struct PalTree {
	Vi txt; // Text for which tree is built

	// Node 0 = empty palindrome (root of even)
	// Node 1 = "-1" palindrome (root of odd)
	Vi len{0, -1}; // Lengths of palindromes
	Vi link{1, 0}; // Suffix palindrome links
	// Edges to next palindromes
	vector<array<int, ALPHA>> to{ {}, {} };
	int last{0}; // Current node (max suffix pal)

	Vi diff{0, 0};   // len[i]-len[link[i]] [EXT]
	Vi slink{0, 0};  // Serial links        [EXT]
	Vi series{0, 0}; // Series DP answer    [EXT]
	Vi ans{0};       // DP answer for prefix[EXT]

	int ext(int i) {
		while (len[i]+2 > sz(txt) ||
		       txt[sz(txt)-len[i]-2] != txt.back())
			i = link[i];
		return i;
	}

	// Append letter from [0;ALPHA); time: O(1)
	// (or O(lg n) if [EXT] is enabled)
	void add(int x) {
		txt.pb(x);
		last = ext(last);

		if (!to[last][x]) {
			len.pb(len[last]+2);
			link.pb(to[ext(link[last])][x]);
			to[last][x] = sz(to);
			to.emplace_back();

			// [EXT]
			diff.pb(len.back() - len[link.back()]);
			slink.pb(diff.back() == diff[link.back()]
				? slink[link.back()] : link.back());
			series.pb(0);
			// [/EXT]
		}
		last = to[last][x];

		// [EXT]
		ans.pb(INT_MAX);
		for (int i=last; len[i] > 0; i=slink[i]) {
			series[i] = ans[sz(ans) - len[slink[i]]
			               - diff[i] - 1];
			if (diff[i] == diff[link[i]])
				series[i] = min(series[i],
				                series[link[i]]);
			ans.back() = min(ans.back(),series[i]+1);
		}
		// [/EXT]
	}
};
