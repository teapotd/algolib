#pragma once
#include "../template.h"

// Computes n! / (k1! * .. * kn!)
//! Source: https://github.com/jacynkaa/kactl/blob/main/content/combinatorial/multinomial.h
ll multinomial(vi& v) {
	ll c = 1, m = v.empty() ? 1 : v[0];
	rep(i, 1, sz(v)) rep(j, 0, v[i])
		c = c * ++m / (j+1);
	return c;
}
