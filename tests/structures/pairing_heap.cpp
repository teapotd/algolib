#include "../../lib/structures/pairing_heap.h"
#include "../testing.h"

int main() {
	srand(123);

	PHeap<int, greater<int>> heap;
	// priority_queue<int> que;

	// for (int i = 0; i < 1000000; i++) {
	// 	int tmp = r(-10000, 10000);
	// 	// que.push(tmp);
	// 	heap.push(tmp);
	// }

	// for (int i = 0; i < 1; i++) {
	// 	// assert(que.empty() == heap.empty());
	// 	int tmp = r(100000, 500000);

	// 	for (int i = 0; i < tmp; i++ ) {
	// 		// printf("%d %d\n", que.top(), heap.top());
	// 		// assert(que.top() == heap.top());
	// 		// que.pop();
	// 		heap.pop();
	// 	}

	// 	for (int i = 0; i < tmp; i++) {
	// 		int tmp = r(-10000, 10000);
	// 		// que.push(tmp);
	// 		heap.push(tmp);
	// 	}
	// }

	for (int i = 0; i < 1000000; i++) {
		int tmp = r(-10000, 10000);
		heap.push(tmp);
	}

	while (!heap.empty()) {
		// printf("%d\n", heap.top());
		heap.pop();
	}

	return 0;
}
