#pragma once
#include "../template.h"

// Get inversion vector for sequence of
// numbers in [0;n); ret[i] = count of numbers
// greater than perm[i] to the left; O(n lg n)
vi encodeInversions(vi perm) {
	vi odd, ret(sz(perm));
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

// Count inversions in sequence of numbers
// in [0;n); time: O(n lg n)
ll countInversions(vi perm) {
	ll ret = 0, cont = 1;
	vi odd;

	while (cont) {
		odd.assign(sz(perm)+1, 0);
		cont = 0;

		rep(i, 0, sz(perm)) {
			if (perm[i] % 2) odd[perm[i]]++;
			else ret += odd[perm[i]+1];
			cont += perm[i] /= 2;
		}
	}
	return ret;
}
