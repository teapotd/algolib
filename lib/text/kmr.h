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
			vector<pair<Pii, int>> tmp;

			rep(j, 0, sz(str)) {
				int a = ids.back()[j], b = -1; 
				if (j+h < sz(str)) b = ids.back()[j+h];
				tmp.pb({ {a, b}, j });
			}

			sort(all(tmp));
			ids.emplace_back(sz(tmp));

			int n = 0;
			rep(j, 0, sz(tmp)) {
				if (j > 0 && tmp[j-1].x != tmp[j].x)
					n++;
				ids.back()[tmp[j].y] = n;
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

	// Compute suffix array of string; O(n)
	Vi sufArray() {
		Vi sufs(sz(ids.back()));
		rep(i, 0, sz(ids.back()))
			sufs[ids.back()[i]] = i;
		return sufs;
	}
};
