#pragma once
#include "../template.h"

constexpr char AMIN = 'a'; // Smallest letter
constexpr int ALPHA = 26; // Set alphabet size

// Suffix automaton - minimal DFA that
// recognizes all suffixes of given string
// (and encodes all substrings);
// space: O(n*ALPHA); time: O(n)
// Paths from root are equivalent to substrings
//! Source: https://cp-algorithms.com/string/suffix-automaton.html
struct SufDFA {
	// State v represents endpos-equivalence
	// class that contains words of all lengths
	// between link[len[v]]+1 and len[v].
	// len[v] = longest word of equivalence class
	// link[v] = link to state of longest suffix
	//           in other equivalence class
	// to[v][c] = automaton edge c from v
	vi len{0}, link{-1};
	vector<array<int, ALPHA>> to{ {} };
	int last{0}; // Current node (whole word)

#if COUNT_SUBSTR_OCCURENCES
	vector<vi> inSufs; // Suffix-link tree
	vi cnt{0};         // Occurence count
#endif
#if COUNT_OUTGOING_PATHS
	vector<ll> paths;  // Out-path count
#endif

	SufDFA() {}

	// Build suffix automaton for given string
	// and compute extended stuff; time: O(n)
	SufDFA(const string& s) {
		each(c, s) add(c);
		finish();
	}

	// Append letter to the back
	void add(char c) {
		int v = last, x = c-AMIN;
		last = sz(len);
		len.pb(len[v]+1);
		link.pb(0);
		to.pb({});
	#if COUNT_SUBSTR_OCCURENCES //!HIDE
		cnt.pb(1); // COUNT_SUBSTR_OCCURENCES
	#endif //!HIDE

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
			#if COUNT_SUBSTR_OCCURENCES //!HIDE
				cnt.pb(0); // COUNT_SUBSTR_OCCURENCES
			#endif //!HIDE
				link[last] = link[q] = sz(len)-1;
				while (v != -1 && to[v][x] == q) {
					to[v][x] = link[q];
					v = link[v];
				}
			}
		}
	}

	// Go using edge `c` from state `i`.
	// Returns 0 if edge doesn't exist.
	int next(int i, char c) {
		return to[i][c-AMIN];
	}

	// Compute extended stuff (offline)
	void finish() {
	#if COUNT_SUBSTR_OCCURENCES
		inSufs.resize(sz(len));
		rep(i, 1, sz(link)) inSufs[link[i]].pb(i);
		dfsSufs(0);
	#endif
	#if COUNT_OUTGOING_PATHS
		paths.assign(sz(len), 0);
		dfs(0);
	#endif
	}

#if COUNT_SUBSTR_OCCURENCES
	void dfsSufs(int v) {
		each(e, inSufs[v]) {
			dfsSufs(e);
			cnt[v] += cnt[e];
		}
	}
#endif

#if COUNT_OUTGOING_PATHS
	void dfs(int v) {
		if (paths[v]) return;
		paths[v] = 1;
		each(e, to[v]) if (e) {
			dfs(e);
			paths[v] += paths[e];
		}
	}

	// Get lexicographically k-th substring
	// of represented string; time: O(|substr|)
	// Empty string has index 0.
	string lex(ll k) {
		string s;
		int v = 0;
		while (k--) rep(i, 0, ALPHA) {
			int e = to[v][i];
			if (e) {
				if (k < paths[e]) {
					s.pb(char(AMIN+i));
					v = e;
					break;
				}
				k -= paths[e];
			}
		}
		return s;
	}
#endif
};
