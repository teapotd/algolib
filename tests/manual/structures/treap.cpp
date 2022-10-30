#include "../../../src/structures/treap.h"
#include "../testing.h"

int n;
vi naive;
Treap treap;
int root;

int main() {
	rep(t, 0, 300) {
		n = r(1, 50);
		naive.resize(n);
		iota(all(naive), 0);

		treap = {n};
		root = 0;
		rep(j, 1, n) root = treap.join(root, j);

		rep(j, 0, 10000) {
			int begin = r(0, n-1), end = r(0, n-1);
			if (begin > end) swap(begin, end);
			reverse(naive.begin()+begin, naive.begin()+end);
			root = treap.reverse(root, begin, end);

			rep(k, 0, n) {
				assert(treap.index(naive[k]) == k);
			}
		}

		rep(i, 0, n) {
			int found = treap.find(root, i);
			assert(naive[i] == found);
		}
	}
	return 0;
}
