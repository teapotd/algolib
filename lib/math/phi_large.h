#pragma once
#include "../template.h"
#include "pollard_rho.h"

// Initialize Pollard Rho first!

ll phi(ll n) {
  each(p, factorize(n)) n = n / p.x * (p.x-1);
  return n;
}
