#pragma once

#include "../template.h"

template<class T, class Cmp = less<T>>
struct PHeap {
	struct Node;
	using NodeP = unique_ptr<Node>; // To disable deallocation: change to Node* (and use bump allocator)

	struct Node {
		T val;
		NodeP child{nullptr}, next{nullptr};
		Node* prev{nullptr};

		Node(T x = T()) { val = x; }

		void setChild(NodeP v) {
			if (child && child->prev == this) child->prev = nullptr;
			child = move(v);
			if (child) child->prev = this;
		}

		void setNext(NodeP v) {
			if (next && next->prev == this) next->prev = nullptr;
			next = move(v);
			if (next) next->prev = this;
		}
	};

	NodeP root{nullptr};

	NodeP merge(NodeP l, NodeP r) {
		if (!l) return move(r);
		if (!r) return move(l);

		if (Cmp()(l->val, r->val)) swap(l, r);

		l->setNext(move(r->child));
		r->setChild(move(l));
		return move(r);
	}

	NodeP mergePairs(NodeP v) {
		if (!v || !v->next) return v;
		NodeP v2 = move(v->next), v3 = move(v2->next);

		v->next = nullptr; v2->next = nullptr;
		v->prev = nullptr; v2->prev = nullptr;
		if (v3) v3->prev = nullptr;

		return merge(merge(move(v), move(v2)), mergePairs(move(v3)));
	}

	Node* push(const T& x) {
		NodeP tmp(new Node(x));
		auto ptr = &*tmp;
		root = merge(move(root), move(tmp));
		return ptr;
	}

	void decrease(Node* v, T val) {
		assert(!Cmp()(v->val, val));
		v->val = val;

		if (!v->prev) return;
		NodeP uniq;

		if (&*v->prev->child == v) {
			uniq = move(v->prev->child);
			v->prev->setChild(move(v->next));
		} else {
			uniq = move(v->prev->next);
			v->prev->setNext(move(v->next));
		}

		uniq->prev = nullptr; uniq->next = nullptr;
		root = merge(move(root), move(uniq));
	}

	bool     empty()          { return !root; }
	const T& top()            { return root->val; }
	void     merge(PHeap&& r) { root = merge(move(root), move(r.root)); r.root = nullptr; }
	void     pop()            { root = mergePairs(move(root->child)); }
};
