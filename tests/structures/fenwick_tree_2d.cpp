#include "../../src/structures/fenwick_tree_2d.h"
#include "../testing.h"

//void bench() {
//	int N = 2000, M = 1000;
//	Fenwick2D tree(N, M);
//
//	rep(t, 0, 1000000) {
//		tree.modify(r(0, N-1), r(0, M-1), 1000);
//		tree.query(r(0, N), r(0, M));
//	}
//}

int main() {
	int N = 2000, M = 1000;
	vector<Vi> naive(N, Vi(M));
	Fenwick2D tree(N, M);
	
	rep(t, 0, 1000) {
		int a = r(0, N-1), b = r(0, M-1);
		int c = r(0, 100);

		tree.modify(a, b, c);
		naive[a][b] += c;

		a = r(0, N);
		b = r(0, M);
		a = N; b = M;

		int fast = tree.query(a, b);
		int slow = 0;
		rep(i, 0, a) rep(j, 0, b) slow += naive[i][j];

		assert(slow == fast);
	}
}
