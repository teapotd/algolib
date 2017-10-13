#include "../template.h"

template<class T, class Cmp = less<T>>
struct PHeap {
	struct Node;
	using NodeP = unique_ptr<Node>;

	struct Node {
		T top;
		NodeP child, next;

		Node(T x = T()) { top = x; }
	};

	NodeP root;

	NodeP merge(NodeP l, NodeP r) {
		if (!l) return move(r);
		if (!r) return move(l);
		assert(l != r);

		if (Cmp()(l->top, r->top)) swap(l, r);

		l->next = move(r->child);
		r->child = move(l);
		return move(r);
	}

	NodeP mergePairs(NodeP v) {
		if (!v || !v->next) return v;
		NodeP v2 = move(v->next), v3 = move(v2->next);
		return merge(merge(move(v), move(v2)), mergePairs(move(v3)));
	}

	bool     empty()          { return !root; }
	const T& top()            { assert(root); return root->top; }
	void     push(const T& x) { root = merge(move(root), NodeP(new Node(x))); }
	void     merge(PHeap&& r) { root = merge(move(root), move(r.root)); }
	void     pop()            { root = mergePairs(move(root->child)); }
};
