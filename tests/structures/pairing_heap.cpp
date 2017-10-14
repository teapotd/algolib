#include "../../lib/util/alloc.h"
#include "../../lib/structures/pairing_heap.h"
#include "../testing.h"

int main() {
	// PHeap<int, greater<int>> heap;
	// priority_queue<int> que;

	// for (int i = 0; i < 1000000; i++) {
	// 	int tmp = r(-10000, 10000);
	// 	que.push(tmp);
	// 	heap.push(tmp);
	// }


	// while (true) {
	// 	assert(que.empty() == heap.empty());
	// 	int tmp = r(100000, 500000);

	// 	for (int i = 0; i < tmp; i++ ) {
	// 		// printf("%d %d\n", que.top(), heap.top());
	// 		assert(que.top() == heap.top());
	// 		que.pop();
	// 		heap.pop();
	// 	}

	// 	for (int i = 0; i < tmp; i++) {
	// 		int tmp = r(-10000, 10000);
	// 		que.push(tmp);
	// 		heap.push(tmp);
	// 	}
	// }

	PHeap<int> heap;
	PHeap<int>::Node* some;

	for (int j = 0; j < 1; j++) {
		PHeap<int> heap2;

		for (int i = 0; i < 15; i++) {
			int tmp = r(-10000, 10000);
			some = heap.push(tmp);
		}

		heap.merge(move(heap2));
	}

	printf("# %d\n", some->val);
	heap.decrease(some, some->val - 1000);

	for (int i = 0; !heap.empty() && i < 20; i++) {
		printf("%d\n", heap.top());
		heap.pop();
	}
	return 0;
}
