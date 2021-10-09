#include "../../../src/structures/li_chao_tree.h"
#include "../testing.h"

struct Naive {
	vector<ll> c;
	Naive(int n = 0) : c(n, ll(-1e9)) {}
	ll query(int x) { return c[x]; }

	void max(int vb, int ve, LiChao::Func f) {
		rep(i, vb, ve) c[i] = ::max(c[i], f.a*i + f.b);
	}

	void add(int vb, int ve, LiChao::Func f) {
		rep(i, vb, ve) c[i] += f.a*i + f.b;
	}
};

void check(LiChao& fast, Naive& naive) {
	vector<ll> fastC(sz(naive.c));
	rep(i, 0, sz(fastC)) fastC[i] = fast.query(i);
	assert(naive.c == fastC);
}

int main() {
	rep(i, 0, 1000) {
		int n = r(1, 1000);
		LiChao fast(n);
		Naive naive(n);

		LiChao::Func f{r(-50, 50), r(-50, 50)};
		fast.max(0, n, f);
		naive.max(0, n, f);

		check(fast, naive);

		rep(j, 0, 1000) {
			int vb = r(0, n), ve = r(0, n);
			f = {r(-50, 50), r(-50, 50)};
			if (r(0, 1)) {
				fast.max(vb, ve, f);
				naive.max(vb, ve, f);
			} else {
				fast.add(vb, ve, f);
				naive.add(vb, ve, f);
			}
			check(fast, naive);
		}
	}
}
