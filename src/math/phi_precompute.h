#pragma once
#include "../template.h"

Vi phi(1e7+1);

// Precompute Euler's totients; time: O(n lg n)
void calcPhi() {
	iota(all(phi), 0);
	rep(i, 2, sz(phi)) if (phi[i] == i)
		for (int j = i; j < sz(phi); j += i)
			phi[j] = phi[j] / i * (i-1);
}
