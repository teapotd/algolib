#pragma once
#include "../template.h"

constexpr char AMIN = 'a'; // Smallest letter
constexpr int ALPHA = 26;  // Alphabet size

// Aho-Corasick algorithm for linear-time
// multiple pattern matching.
// Add patterns using add(), then call build().
struct Aho {
	struct Node {
		int nxt[ALPHA], suf{-1}, accLink{-1};
		Vi accept;
	};

	vector<Node> V;
	Aho() { init(); }
	void init() { V.assign(1, {}); }

	// Add string with given ID to structure
	void add(const string& str, int id) {
		int i = 0;
		each(c, str) {
			if (!V[i].nxt[c-AMIN]) {
				V[i].nxt[c-AMIN] = sz(V);
				V.emplace_back();
			}
			i = V[i].nxt[c-AMIN];
		}
		V[i].accept.pb(id);
	}

	// Build automata
	void build() {
		queue<int> que;
		each(e, V[0].nxt) if (e) {
			V[e].suf = 0;
			que.push(e);
		}
		while (!que.empty()) {
			int i = que.front(), s = V[i].suf, j = 0;
			que.pop();
			each(e, V[i].nxt) {
				if (e) que.push(e);
				(e ? V[e].suf : e) = V[s].nxt[j++];
			}
			V[i].accLink = (V[s].accept.empty() ?
					V[s].accLink : s);
		}
	}

	// Append `c` to state `i`
	int nxt(int i, char c) {
		return V[i].nxt[c-AMIN];
	}

	// Call `f` for each pattern accepted
	// when in state `i` with its ID as argument.
	// Return true from `f` to terminate early.
	// Calls are in descreasing length order.
	template<class F> void accepted(int i, F f) {
		while (i != -1) {
			each(a, V[i].accept) if (f(a)) return;
			i = V[i].accLink;
		}
	}
};
