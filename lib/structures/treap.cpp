#pragma once
#include "../template.h"
// UNTESTED

struct Treap {
	using T = int;
	Treap *left{0}, *right{0};
	int weight{rand()};
	T key;

	Treap(T k) : key(k) {}
	~Treap() { delete left; delete right; }
};

void push(Treap* node) {
	if (node) { /* Propagate down stuff */ }
}

void update(Treap* node) {
	if (node) { /* Update queries stuff */ }
}

void split(Treap* root, Treap*& small,
	         Treap*& great, Treap::T by) {
	push(root);
	if (!root) {
		small = great = 0;
	} else if (by <= root->key) {
		split(root->left, small, root->left, by);
		great = root;
	} else {
		split(root->right, root->right, great, by);
		small = root;
	}
	update(root);
}

Treap* join(Treap* small, Treap* great) {
	push(small);
	push(great);
	if (!small) return great;
	if (!great) return small;
	if (small->weight < great->weight) {
		small->right = join(small->right, great);
		update(small);
		return small;
	}
	great->left = join(small, great->left);
	update(great);
	return great;
}

Treap*& find(Treap*& root, Treap::T key) {
	push(root);
	if (!root || root->key == key) return root;
	return (key < root->key ?
		      find(root->left, key) :
		      find(root->right, key));
}
