#include "../../lib/trees/link_cut_tree.h"
#include "../testing.h"

constexpr int N = 100;
constexpr int OPS = 10000;
constexpr int MIN_COMPS = 30;
constexpr int MAX_COMPS = 60;

LinkCutTree tree;
vector<Vi> G;
vector<int> comps;
int nComps = 0;

void dfs(int i, int c) {
	comps[i] = c;
	each(e, G[i]) if (comps[e] < 0) dfs(e, c);
}

void calcComps() {
	nComps = 0;
	comps.assign(sz(G), -1);
	rep(i, 0, sz(G)) if (comps[i] < 0) dfs(i, ++nComps);
}

void modify() {
	calcComps();

	vector<Pii> toAdd, toCut;
	rep(i, 0, sz(G)) each(j, G[i]) {
		toCut.pb({ i, j });
	}
	rep(i, 0, sz(G)) rep(j, 0, sz(G)) if (comps[i] != comps[j]) {
		toAdd.pb({ i, j });
	}

	bool add;

	if (nComps <= MIN_COMPS) {
		add = 0;
	} else if (nComps >= MAX_COMPS) {
		add = 1;
	} else {
		add = r(0, 1);
	}

	if (add) {
		Pii e = toAdd[r(0, sz(toAdd)-1)];
		tree.link(e.x, e.y);
		G[e.x].pb(e.y);
		G[e.y].pb(e.x);
	} else {
		Pii e = toCut[r(0, sz(toCut)-1)];
		tree.cut(e.x, e.y);
		G[e.x].erase(find(all(G[e.x]), e.y));
		G[e.y].erase(find(all(G[e.y]), e.x));
	}
}

void check() {
	calcComps();

	rep(i, 0, sz(G)) rep(j, 0, sz(G)) {
		bool valid = (comps[i] == comps[j]);
		bool answer = (tree.find(i) == tree.find(j));

		if (valid != answer) {
			deb(i, j, valid, answer);
			exit(0);
		}
	}
}

int main() {
	G.resize(N);
	tree.init(N);
	check();

	rep(i, 0, OPS) {
		modify();
		check();
		// deb(nComps);
	}
  return 0;
}
