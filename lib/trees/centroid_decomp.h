#include "../template.h"

struct node {
	vector<node*> E, cE;
	Vi dists;
	int cDepth{-1}, cSize{0}, cState{0};
};

void dfsSize(node* v, int dep) {
	v->cDepth = dep;
	v->cSize = 1;
	v->cState = 0;

	each(e, v->E) if (e->cState <= 1 && e->cDepth < dep) {
		dfsSize(e, dep);
		v->cSize += e->cSize;
	}
}

void dfsDist(node* v, int d) {
	v->cState = 1;
	each(e, v->E) if (!e->cState) {
		e->dists.pushb(d+1);
		dfsDist(e, d+1);
	}
}

node* centroidDecomp(node* v, int dep) {
	dfsSize(v, dep);

	int size = v->cSize;
	node *par = 0, *heavy = 0;

	while (true) {
		int hSize = 0;

		each(e, v->E) if (e != par && e->cDepth == dep) {
			hSize = e->cSize;
			heavy = e;
		}

		if (hSize <= size/2) break;
		par = v; v = heavy;
	}

	dfsDist(v, 0);
	v->cSize = size;
	v->cState = 2;

	each(e, v->E) if (e->cDepth == dep) v->cE.pushb(centroidDecomp(e, dep+1));
	return v;
}
