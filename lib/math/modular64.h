#pragma once
#include "../template.h"

ll modAdd(ll x, ll y, ll m) {
  x += y;
  return (x < m ? x : x-m);
}

ll modSub(ll x, ll y, ll m) {
  x -= y;
  return (x >= 0 ? x : x+m);
}

ll modMul(ll x, ll y, ll m) {
  ll t = 0;
  while (y) {
    if (y & 1) t = modAdd(t, x, m);
    y >>= 1;
    x = modAdd(x, x, m);
  }
  return t;
}

ll modPow(ll x, ll e, ll m) {
  ll t = 1;
  while (e) {
    if (e & 1) t = modMul(t, x, m);
    e >>= 1;
    x = modMul(x, x, m);
  }
  return t;
}
