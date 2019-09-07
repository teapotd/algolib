#pragma once
#include "../template.h"
#include "pollard_rho.h"

// Compute Euler's totient of large numbers
// time: O(n^(1/4)) <- factorization
ll phi(ll n) {
	each(p, factorize(n)) n = n / p.x * (p.x-1);
	return n;
}
