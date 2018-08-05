#pragma once
#include "../template.h"

struct Vert {
  Vi edges;
  int parent, size, depth, chain, chainPos;
};

struct Chain {
  Vi verts;
};

vector<Vert> G;
vector<Chain> chains;

void hld(int i, int parent = -1, int d = 0) {
  int h = -1;
  G[i].parent = parent;
  G[i].depth = d;
  G[i].size = 1;

  each(e, G[i].edges) if (e != parent) {
    hld(e, i, d+1);
    G[i].size += G[e].size;
    if (h < 0 || G[h].size < G[e].size) h = e;
  }

  if (h < 0) {
    h = sz(chains);
    chains.emplace_back();
  } else {
    h = G[h].chain;
  }
  chains[h].verts.pb(i);
  G[i].chain = h;

  if (parent < 0) {
    each(p, chains) {
      reverse(all(p.verts));
      rep(j, 0, sz(p.verts))
        G[p.verts[j]].chainPos = j;
    }
  }
}

int laq(int i, int level) {
  while (true) {
    int k = G[i].chainPos - (G[i].depth-level);
    if (k >= 0)
      return chains[G[i].chain].verts[k];
    i = G[chains[G[i].chain].verts[0]].parent;
  }
}

int lca(int a, int b) {
  while (G[a].chain != G[b].chain) {
    int ha = chains[G[a].chain].verts[0];
    int hb = chains[G[b].chain].verts[0];
    if (G[ha].depth > G[hb].depth)
      a = G[ha].parent;
    else
      b = G[hb].parent;
  }
  return G[a].depth < G[b].depth ? a : b;
}
