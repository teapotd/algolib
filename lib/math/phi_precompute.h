#pragma once
#include "../template.h"

constexpr int MAX_PHI = 10e6;
Vi phi(MAX_PHI+1);

void calcPhi() {
  rep(i, 0, MAX_PHI+1) phi[i] = i;

  for (int i = 2; i <= MAX_PHI; i++)
    if (phi[i] == i)
      for (int j = i; j <= MAX_PHI; j += i)
        phi[j] = phi[j] / i * (i-1);
}
