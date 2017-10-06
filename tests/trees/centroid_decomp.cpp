#include "../../lib/trees/centroid_decomp.h"
#include "../testing.h"

vector<Vert> graph;

void edge(int i, int j) {
	graph[i-1].edges.push_back(&graph[j-1]);
	graph[j-1].edges.push_back(&graph[i-1]);
}

void dfs(Vert* vert, Vert* parent = nullptr, int indent = 0) {
	for (int i = 0; i < indent; i++) {
		printf(" ");
	}
	printf("%d (%d/%d): ", int(vert - graph.data()) + 1, vert->cDepth, vert->cSize);

	for (int x : vert->dists) {
		printf("%d ", x);
	}
	printf("\n");

	for (Vert* edge : vert->cEdges) {
		if (edge != parent) {
			dfs(edge, vert, indent+4);
		}
	}
}

int main() {
	graph.resize(16);

	edge(1, 4);
	edge(2, 4);
	edge(3, 4);
	edge(4, 5);
	edge(5, 6);
	edge(6, 7);
	edge(7, 8);
	edge(7, 9);
	edge(6, 10);
	edge(10, 11);
	edge(11, 12);
	edge(12, 14);
	edge(11, 13);
	edge(13, 15);
	edge(13, 16);

	dfs(centroidDecomp(&graph[0], 0));
	return 0;
}
