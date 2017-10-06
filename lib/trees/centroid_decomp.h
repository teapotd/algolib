#include "../template.h"

struct Vert {
	vector<Vert*> edges, cEdges;
	Vi dists;
	int cDepth{-1}, cSize{0}, cState{0};
};

void dfsSize(Vert* v, int depth) {
	v->cDepth = depth;
	v->cSize = 1;
	v->cState = 0;

	each(e, v->edges) if (e->cState <= 1 && e->cDepth < depth) {
		dfsSize(e, depth);
		v->cSize += e->cSize;
	}
}

void dfsDist(Vert* v, int dist) {
	v->cState = 1;
	each(e, v->edges) if (!e->cState) {
		e->dists.push_back(dist+1);
		dfsDist(e, dist+1);
	}
}

Vert* centroidDecomp(Vert* v, int depth) {
	dfsSize(v, depth);

	int size = v->cSize;
	Vert *parent = 0, *heavy = 0;

	while (true) {
		int hSize = 0;

		each(e, v->edges) if (e != parent && e->cDepth == depth) {
			hSize = e->cSize;
			heavy = e;
		}

		if (hSize <= size/2) break;
		parent = v; v = heavy;
	}

	dfsDist(v, 0);
	v->cSize = size;
	v->cState = 2;

	each(e, v->edges) if (e->cDepth == depth) v->cEdges.push_back(centroidDecomp(e, depth+1));
	return v;
}
