#pragma once
#include "../template.h"

// Get inversion vector for permutation of
// numbers in [0;n); ret[i] = count of numbers
// smaller than perm[i] to the left; O(n lg n)
Vi encodeInversions(Vi perm) {
	Vi odd, ret(sz(perm));
	int cont = 1;

	while (cont) {
		odd.assign(sz(perm)+1, 0);
		cont = 0;

		rep(i, 0, sz(perm)) {
			if (perm[i] % 2) odd[perm[i]]++;
			else ret[i] += odd[perm[i]+1];
			cont += perm[i] /= 2;
		}
	}
	return ret;
}
