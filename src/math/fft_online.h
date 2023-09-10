#pragma once
#include "../template.h"
#include "modular.h"
#include "fft_mod.h"

// Online convolution helper. Ensures that:
// out[m] = sum { f(i)*g(m-i) : 1 <= i <= m-1 }
// See usage example below.
template<class F, class G>
void onlineConv(vector<Zp>& out, int m,
                F f, G g) {
	int len = m & ~(m-1), b = m-len;
	int e = min(m+len, sz(out));
	auto apply = [&](auto r, auto s) {
		vector<ll> P(m-b+1), Q(min(e-b, m));
		rep(i, max(b, 1), m) P[i-b] = r(i).x;
		rep(i, 1, sz(Q)) Q[i] = s(i).x;
		convolve(P, Q);
		rep(i, m, e) out[i] += P[i-b];
	};
	apply(f, g);
	if (b) apply(g, f);
}

// h[m] = 1 + sum h(i)*i * h(m-i)/(m-i)
void example(int n) {
	vector<Zp> h(n);
	for (int m = 1; m < n; m++) {
		onlineConv(h, m,
			[&](int i) { return h[i] * i; },
			[&](int i) { return h[i] / i; });
		h[m] += 1;
	}
}
