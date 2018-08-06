#pragma once
#include "../template.h"
#include "modular.h"
//!!IGNORE Something's wrong sometimes

// Montgomery modular multiplication
// MOD < MG_MULT, gcd(MG_MULT, MOD) must be 1

constexpr ll MG_SHIFT = 32;
constexpr ll MG_MULT  = 1LL << MG_SHIFT;
constexpr ll MG_MASK  = MG_MULT - 1;
const ll MG_INV = MG_MULT-modInv(MOD, MG_MULT);

// Convert to Montgomery form
ll MG(ll x) { return (x*MG_MULT) % MOD; }

// Montgomery reduction
// redc(mg * mg) = Montgomery-form product
// redc(notMg * mg) = not montgomery
ll redc(ll x) {
	ll q = (x * MG_INV) & MG_MASK;
	x = (x + q*MOD) >> MG_SHIFT;
	return (x >= MOD ? x-MOD : x);
}
