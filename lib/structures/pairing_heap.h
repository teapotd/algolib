#pragma once

#include "../template.h"

template<class T, class Cmp = less<T>>
struct PHeap {
	struct Node;
	using NodeP = unique_ptr<Node>; // To disable deallocation: change to single_ptr (and use bump allocator)

	struct Node {
		T val;
		NodeP child{nullptr}, next{nullptr};
		Node* prev{nullptr};

		Node(T x = T()) { val = x; }

		NodeP moveChild() {
			if (child) child->prev = nullptr;
			return move(child);
		}

		NodeP moveNext() {
			if (next) next->prev = nullptr;
			return move(next);
		}

		void setChild(NodeP v) {
			if (child) child->prev = nullptr;
			child = move(v);
			if (child) child->prev = this;
		}

		void setNext(NodeP v) {
			if (next) next->prev = nullptr;
			next = move(v);
			if (next) next->prev = this;
		}
	};

	NodeP root{nullptr};

	NodeP merge(NodeP l, NodeP r) {
		if (!l) return move(r);
		if (!r) return move(l);

		if (Cmp()(l->val, r->val)) swap(l, r);

		l->setNext(r->moveChild());
		r->setChild(move(l));
		return move(r);
	}

	NodeP mergePairs(NodeP v) {
		if (!v || !v->next) return v;
		NodeP v2 = v->moveNext(), v3 = v2->moveNext();
		return merge(merge(move(v), move(v2)), mergePairs(move(v3)));
	}

	Node* push(const T& x) {
		NodeP tmp(new Node(x));
		auto ret = &*tmp;
		root = merge(move(root), move(tmp));
		return ret;
	}

	void decrease(Node* v, T val) {
		assert(!Cmp()(v->val, val));
		v->val = val;

		auto prev = v->prev;
		if (!prev) return;
		NodeP uniq;

		if (&*v->prev->child == v) {
			uniq = prev->moveChild();
			prev->setChild(v->moveNext());
		} else {
			uniq = prev->moveNext();
			prev->setNext(v->moveNext());
		}

		root = merge(move(root), move(uniq));
	}

	bool     empty()          { return !root; }
	const T& top()            { return root->val; }
	void     merge(PHeap&& r) { root = merge(move(root), move(r.root)); r.root = nullptr; }
	void     pop()            { root = mergePairs(root->moveChild()); }
};
