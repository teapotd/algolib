#pragma once
#include "../template.h"

constexpr int ALPHA = 26; // Set alphabet size

// Suffix automaton - minimal DFA that
// recognizes all suffixes of given string
// (and encodes all substrings);
// space: O(n*ALPHA); time: O(n)
//! Source: https://cp-algorithms.com/string/suffix-automaton.html
struct SufDFA {
	Vi len{0}, link{-1};
	vector<array<int, ALPHA>> to{ {} };
	int last{0}; // Current node (whole word)

	// Append letter from [0;ALPHA) to the back
	void add(int x) {
		int v = last;
		last = sz(len);
		len.pb(len[v]+1);
		link.pb(0);
		to.pb({});

		while (v != -1 && !to[v][x]) {
			to[v][x] = last;
			v = link[v];
		}

		if (v != -1) {
			int q = to[v][x];

			if (len[v]+1 == len[q]) {
				link[last] = q;
			} else {
				len.pb(len[v]+1);
				link.pb(link[q]);
				to.pb(to[q]);
				link[last] = link[q] = sz(len)-1;

				while (v != -1 && to[v][x] == q) {
					to[v][x] = link[q];
					v = link[v];
				}
			}
		}
	}
};
