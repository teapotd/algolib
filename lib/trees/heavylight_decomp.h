#pragma once
#include "../template.h"
// UNTESTED

struct Vert {
  Vi edges;
  int size, level, chain, chainPos;
};

struct Chain {
  Vi verts;
};

vector<Vert> G;
vector<Chain> chains;

void hld(int i, int parent = -1, int d = 0) {
  int h = -1;
  G[i].size = 1;
  G[i].level = d;

  each(e, G[i].edges) if (e != parent) {
    hld(e, i, d+1);
    G[i].size += G[e].size;
    if (h < 0 || G[h].size < G[e].size) h = e;
  }

  if (h < 0) {
    h = sz(chains);
    chains.emplace_back();
  }
  chains[h].verts.pb(i);
  G[i].chain = h;

  if (parent < 0) {
    each(p, chains) {
      reverse(all(p.verts));
      rep(j, 0, sz(p.verts)) G[j].chainPos = j;
    }
  }
}
