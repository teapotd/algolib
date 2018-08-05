#pragma once
#include "../template.h"

using ull = uint64_t;

struct BitMatrix {
  vector<ull> M;
  int rows, cols, stride;

  BitMatrix(int n=0, int m=0) { init(n, m); }
  void init(int n, int m) {
    rows = n; cols = m;
    stride = (m+63)/64;
    M.resize(n*stride);
  }

  ull* row(int i) { return &M[i*stride]; }

  bool operator()(int i, int j) {
    return (row(i)[j/64] >> (j%64)) & 1;
  }

  void set(int i, int j, bool val) {
    ull &w = row(i)[j/64], m = 1 << (j%64);
    if (val) w |= m;
    else w &= ~m;
  }
};
