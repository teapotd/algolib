#pragma once
#include "../template.h"

constexpr int ALPHA = 26; // Set alphabet size

// Tree of all palindromes in string,
// constructed online by appending letters.
// space: O(n*ALPHA); time: O(n)
struct PalTree {
	vi txt; // Text for which tree is built

	// Node 0 = empty palindrome (root of even)
	// Node 1 = "-1" palindrome (root of odd)
	vi len{0, -1}; // Lengths of palindromes
	vi link{1, 0}; // Suffix palindrome links
	// Edges to next palindromes
	vector<array<int, ALPHA>> to{ {}, {} };
	int last{0}; // Current node (max suffix pal)

#if MIN_PALINDROME_PARTITION
	// An extension that computes minimal
	// palindromic partition in O(n log n).
	vi diff{0, 0};   // len[i]-len[link[i]]
	vi slink{0, 0};  // Serial links
	vi series{0, 0}; // Series DP answer
	vi ans{0};       // DP answer for prefix
#endif

	int ext(int i) {
		while (len[i]+2 > sz(txt) ||
		       txt[sz(txt)-len[i]-2] != txt.back())
			i = link[i];
		return i;
	}

	// Append letter from [0;ALPHA); time: O(1)
	// (or O(lg n) for MIN_PALINDROME_PARTITION)
	void add(int x) {
		txt.pb(x);
		last = ext(last);

		if (!to[last][x]) {
			len.pb(len[last]+2);
			link.pb(to[ext(link[last])][x]);
			to[last][x] = sz(to);
			to.pb({});

		#if MIN_PALINDROME_PARTITION
			diff.pb(len.back() - len[link.back()]);
			slink.pb(diff.back() == diff[link.back()]
				? slink[link.back()] : link.back());
			series.pb(0);
		#endif
		}
		last = to[last][x];

	#if MIN_PALINDROME_PARTITION
		ans.pb(INT_MAX);
		for (int i=last; len[i] > 0; i=slink[i]) {
			series[i] = ans[sz(ans) - len[slink[i]]
			               - diff[i] - 1];
			if (diff[i] == diff[link[i]])
				series[i] = min(series[i],
				                series[link[i]]);
			// If you want only even palindromes
			// set ans only for sz(txt)%2 == 0
			ans.back() = min(ans.back(),series[i]+1);
		}
	#endif
	}
};
