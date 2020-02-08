#include "../../src/structures/wavelet_tree.h"
#include "../testing.h"

int kth_naive(const Vi& seq, int begin, int end, int k) {
	Vi tmp;
	rep(i, begin, end) tmp.pb(seq[i]);
	sort(all(tmp));
	return tmp[k];
}

int count_naive(const Vi& seq, int begin, int end, int vb, int ve) {
	int ret = 0;
	rep(i, begin, end) ret += (seq[i] >= vb && seq[i] < ve);
	return ret;
}

int main() {
	rep(t, 0, 100) {
		int n = r(1, 1000);
		int maxVal = r(1, 1000);
		Vi seq(n);
		each(s, seq) s = r(0, maxVal-1);

		WaveletTree tree(seq, maxVal);

		rep(i, 0, 10000) {
			int begin = r(0, n-1);
			int end = r(0, n-1);
			if (begin > end) swap(begin, end);
			end++;

			int k = r(0, end-begin-1);
			int fast = tree.kth(begin, end, k);
			int naive = kth_naive(seq, begin, end, k);
			// deb(fast, naive);
			assert(fast == naive);

			int vb = r(0, maxVal-1);
			int ve = r(0, maxVal-1);
			if (vb > ve) swap(vb, ve);
			ve++;
			fast = tree.count(begin, end, vb, ve);
			naive = count_naive(seq, begin, end, vb, ve);
			// deb(fast, naive);
			assert(fast == naive);
		}
	}
	return 0;
}
