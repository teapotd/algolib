#include "../../lib/structures/treap.h"
#include "../testing.h"

int n;
Vi naive;
Treap treap;
int root;

void modify() {
	int begin = r(0, n-1), end = r(0, n-1);
	if (begin > end) swap(begin, end);

	// deb(begin, end, naive);
	reverse(naive.begin()+begin, naive.begin()+end);
	root = treap.reverse(root, begin, end);
}

void check() {
	rep(i, 0, n) {
		int found = treap.find(root, i);
		// deb(i, naive[i], found);
		assert(naive[i] == found);
	}
}

int main() {
	rep(i, 0, 1000) {
		n = r(1, 20);
		naive.resize(n);
		iota(all(naive), 0);

		treap.init(n);
		root = 0;
		rep(j, 1, n) root = treap.join(root, j);

		check();

		rep(j, 0, 10000) {
			modify();
			check();
		}
	}
	return 0;
}
