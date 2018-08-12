#pragma once
#include "../template.h"

struct Vert {
	Vi E, cE;
	int cParent{-2}, cDepth{-1}, cSize{-1};
};

vector<Vert> G;

bool can(int e, int p) {
	return e != p && G[e].cParent == -2;
}

int computeSize(int i, int p) {
	int& s = G[i].cSize = 1;
	each(e, G[i].E) if (can(e, p))
		s += computeSize(e, i);
	return s;
}

int getCentroid(int i) {
	int p = -1, size = computeSize(i, -1);
	bool ok = true;
	while (ok) {
		ok = false;
		each(e, G[i].E) if (can(e, p)) {
			if (G[e].cSize > size/2) {
				p = i; i = e; ok = true;
				break;
			}
		}
	}
	G[i].cSize = size;
	return i;
}

int centroidDecomp(int i, int depth = 0) {
	i = getCentroid(i);
	G[i].cParent = -1;
	G[i].cDepth = depth;

	each(e, G[i].E) if (can(e, -1)) {
		G[i].cE.pb(centroidDecomp(e, depth+1));
		G[G[i].cE.back()].cParent = i;
	}
	return i;
}

