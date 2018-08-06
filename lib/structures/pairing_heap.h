#pragma once
#include "../template.h"

// Pairing heap implementation
// Elements are stored in vector for faster
// allocation. It's MINIMUM queue.
// Allows to merge heaps in O(1)
template<class T, class Cmp = less<T>>
struct PHeap {
	struct Node {
		T val;
		int child{-1}, next{-1}, prev{-1};

		Node(T x = T()) : val(x) {}
	};

	using Vnode = vector<Node>;
	Vnode& M;
	int root{-1};

	int unlink(int& i) {
		if (i >= 0) M[i].prev = -1;
		int x = i; i = -1;
		return x;
	}

	void link(int host, int& i, int val) {
		if (i >= 0) M[i].prev = -1;
		i = val;
		if (i >= 0) M[i].prev = host;
	}

	int merge(int l, int r) {
		if (l < 0) return r;
		if (r < 0) return l;
		if (Cmp()(M[l].val, M[r].val)) swap(l, r);

		link(l, M[l].next, unlink(M[r].child));
		link(r, M[r].child, l);
		return r;
	}

	int mergePairs(int v) {
		if (v < 0 || M[v].next < 0) return v;
		int v2 = unlink(M[v].next);
		int v3 = unlink(M[v2].next);
		return merge(merge(v, v2), mergePairs(v3));
	}

	// ---

	// Initialize heap with given node storage
	// Just declare 1 Vnode and pass it to heaps
	PHeap(Vnode& mem) : M(mem) {}

	// Add given key to heap, returns index; O(1)
	int push(const T& x) {
		int index = sz(M);
		M.emplace_back(x);
		root = merge(root, index);
		return index;
	}

	// Change key of i to smaller value; O(1)
	void decrease(int i, T val) {
		assert(!Cmp()(M[i].val, val));
		M[i].val = val;

		int prev = M[i].prev;
		if (prev < 0) return;

		auto& p = M[prev];
		link(prev, (p.child == i ? p.child
			   : p.next), unlink(M[i].next));

		root = merge(root, i);
	}

	bool empty() { return root < 0; }
	const T& top() { return M[root].val; }

	// Merge with other heap. Must use same vec.
	void merge(PHeap& r) { // time: O(1)
		assert(&M == &r.M);
		root = merge(root, r.root); r.root = -1;
	}

	// Remove min element; time: O(lg n)
	void pop() {
		root = mergePairs(unlink(M[root].child));
	}
};
