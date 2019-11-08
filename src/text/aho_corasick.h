#pragma once
#include "../template.h"

constexpr char AMIN = 'a'; // Smallest letter
constexpr int ALPHA = 26;  // Alphabet size

// Aho-Corasick algorithm for linear-time
// multiple pattern matching.
// Add patterns using add(), then call build().
struct Aho {
	vector<array<int, ALPHA>> nxt{1};
	Vi suf = {-1}, accLink = {-1};
	vector<Vi> accept{1};

	// Add string with given ID to structure
	// Returns index of accepting node
	int add(const string& str, int id) {
		int i = 0;
		each(c, str) {
			if (!nxt[i][c-AMIN]) {
				nxt[i][c-AMIN] = sz(nxt);
				nxt.pb({}); suf.pb(-1);
				accLink.pb(1); accept.pb({});
			}
			i = nxt[i][c-AMIN];
		}
		accept[i].pb(id);
		return i;
	}

	// Build automata; time: O(V*ALPHA)
	void build() {
		queue<int> que;
		each(e, nxt[0]) if (e) {
			suf[e] = 0; que.push(e);
		}
		while (!que.empty()) {
			int i = que.front(), s = suf[i], j = 0;
			que.pop();
			each(e, nxt[i]) {
				if (e) que.push(e);
				(e ? suf[e] : e) = nxt[s][j++];
			}
			accLink[i] = (accept[s].empty() ?
					accLink[s] : s);
		}
	}

	// Append `c` to state `i`
	int next(int i, char c) {
		return nxt[i][c-AMIN];
	}

	// Call `f` for each pattern accepted
	// when in state `i` with its ID as argument.
	// Return true from `f` to terminate early.
	// Calls are in descreasing length order.
	template<class F> void accepted(int i, F f) {
		while (i != -1) {
			each(a, accept[i]) if (f(a)) return;
			i = accLink[i];
		}
	}
};
