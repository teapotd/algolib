#include "../../src/structures/segment_tree_multi.h"
#include "../testing.h"

int main() {
	SegmentTreeMulti tree;
	tree.init({ 10, 10, 10 });
	tree.query(0, 2, 0, 2, 0, 2);
	return 0;
}
