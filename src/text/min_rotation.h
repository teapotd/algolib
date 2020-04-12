#pragma once
#include "../template.h"

// Find lexicographically smallest
// rotation of s; time: O(n)
// Returns index where shifted word starts.
// You can use std::rotate to get the word:
// rotate(s.begin(), s.begin()+minRotation(s),
//        s.end());
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/MinRotation.h
int minRotation(string s) {
	int a = 0, n = sz(s); s += s;
	rep(b, 0, n) rep(i, 0, n) {
		if (a+i == b || s[a+i] < s[b+i]) {
			b += max(0, i-1); break;
		}
		if (s[a+i] > s[b+i]) {
			a = b; break;
		}
	}
	return a;
}
