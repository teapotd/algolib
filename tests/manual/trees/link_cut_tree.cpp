#include "../../../src/trees/link_cut_tree.h"
#include "../testing.h"

constexpr int N = 100;
constexpr int OPS = 4000;
constexpr int MIN_COMPS = 5;
constexpr int MAX_COMPS = 60;

LinkCutTree tree;
vector<vi> G;
vector<int> comps, dists;
int nComps = 0;

void dfsDists(int i, int d) {
	dists[i] = d;
	each(e, G[i]) if (dists[e] == INF) dfsDists(e, d+1);
}

void calcDists(int i) {
	dists.assign(sz(G), INF);
	dfsDists(i, 0);
}

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

	vector<pii> toAdd, toCut;
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
		pii e = toAdd[r(0, sz(toAdd)-1)];
		tree.link(e.x, e.y);
		G[e.x].pb(e.y);
		G[e.y].pb(e.x);
	} else {
		pii e = toCut[r(0, sz(toCut)-1)];
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

	rep(i, 0, sz(G)) {
		calcDists(i);
		rep(j, 0, sz(G)) {
			int valid = dists[j];
			int answer = tree.dist(i, j);
			if (valid != answer) {
				deb(i, j, valid, answer);
				exit(0);
			}
		}
	}
}

void benchmark() {
	constexpr int nVerts = 1000000;
	constexpr int TIMES = 2;

	vector<pii> edges;
	tree = {nVerts};

	rep(times, 0, TIMES) {
		edges.clear();
		rep(i, 1, nVerts) {
			edges.pb({ r(0, i-1), i });
		}

		random_shuffle(all(edges));

		each(e, edges) {
			tree.link(e.x, e.y);
			tree.find(r(0, nVerts-1));
		}

		random_shuffle(all(edges));

		each(e, edges) {
			tree.cut(e.x, e.y);
			tree.find(r(0, nVerts-1));
		}
	}

	int nLink = nVerts*TIMES;
	int nCut = nVerts*TIMES*2;
	int nFind = nVerts*TIMES;
	deb(nLink, nCut, nFind);
}

int main() {
	benchmark();

	G.resize(N);
	tree = {N};
	check();

	rep(i, 0, OPS) {
		modify();
		check();
		// deb(nComps);
	}
  return 0;
}
