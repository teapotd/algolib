#pragma once
#include "../template.h"
#include "modular.h"
//!!IGNORE
// Something's wrong

// MOD < MG_MULT, gcd(MG_MULT, MOD) must be 1
// redc(mg * mg) = Montgomery-form product
// redc(notMg * mg) = not montgomery

constexpr ll MG_SHIFT = 32;
constexpr ll MG_MULT  = 1LL << MG_SHIFT;
constexpr ll MG_MASK  = MG_MULT - 1;
const ll MG_INV = MG_MULT-modInv(MOD, MG_MULT);

ll MG(ll x) { return (x*MG_MULT) % MOD; }

ll redc(ll x) {
	ll q = (x * MG_INV) & MG_MASK;
	x = (x + q*MOD) >> MG_SHIFT;
	return (x >= MOD ? x-MOD : x);
}
