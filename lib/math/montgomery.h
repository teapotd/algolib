#pragma once

#include "../template.h"
#include "mod_inv.h"

constexpr ll MG_SHIFT = 32;
constexpr ll MG_MULT  = 1LL << MG_SHIFT;
constexpr ll MG_MASK  = MG_MULT - 1;

ll getMgInv(ll mod)      { return MG_MULT - modInv(mod, MG_MULT); }
ll mgShift(ll n, ll mod) { return (n * MG_MULT) % mod; } // Precompute multipliers

ll redc(ll n, ll mod, ll mgInv) {
	ll quot = (n * mgInv) & MG_MASK;
	n = (n + quot*mod) >> MG_SHIFT;
	return (n >= mod ? n-mod : n);
}

// MOD < MG_MULT, gcd(MG_MULT, MOD) must be 1
// mgRedc(mgForm1 * mgForm2)    = Montgomery-form product
// mgRedc(notMgForm1 * mgForm2) = normal number
