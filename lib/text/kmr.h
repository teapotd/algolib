#pragma once
#include "../template.h"

// KMR algorithm for O(1) lexicographical
// comparison of substrings.
struct KMR {
	vector<Vi> ids;

	KMR() {}

	// Initialize structure; time: O(n lg^2 n)
	// You can change str type to Vi freely.
	explicit KMR(const string& str) {
		ids.clear();
		ids.pb(Vi(all(str)));

		for (int h = 1; h <= sz(str); h *= 2) {
			vector<pair<Pii, int>> pairs;

			rep(j, 0, sz(str)) {
				int a = ids.back()[j], b = -1; 
				if (j+h < sz(str)) b = ids.back()[j+h];
				pairs.pb({ {a, b}, j });
			}

			sort(all(pairs));
			ids.emplace_back(sz(pairs));

			int n = 1;
			rep(j, 0, sz(pairs)) {
				if (j>0 && pairs[j-1].x != pairs[j].x)
					n++;
				ids.back()[pairs[j].y] = n;
			}
		}
	}

	// Get representative of [begin;end); O(1)
	Pii get(int begin, int end) {
		if (begin >= end) return {0, 0};
		int k = 31 - __builtin_clz(end-begin);
		return {ids[k][begin], ids[k][end-(1<<k)]};
	}

	// Compare [b1;e1) with [b2;e2); O(1)
	// Returns -1 if <, 0 if ==, 1 if >
	int cmp(int b1, int e1, int b2, int e2) {
		int l1 = e1-b1, l2 = e2-b2;
		int l = min(l1, l2);
		Pii x = get(b1, b1+l), y = get(b2, b2+l);

		if (x == y) return (l1 > l2) - (l1 < l2);
		return (x > y) - (x < y);
	}
};
