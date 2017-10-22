#include "../../lib/structures/pairing_heap.h"
#include "../testing.h"

PHeap<int>::Vnode heapMem;

int main() {
	// PHeap<int> heap(heapMem);
	// priority_queue<int, vector<int>, greater<int>> que;

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
	// 		int x = r(-10000, 10000);
	// 		que.push(x);
	// 		heap.push(x);
	// 	}
	// }

	// PHeap<int> heap(heapMem);
	// int some;

	// for (int j = 0; j < 1; j++) {
	// 	PHeap<int> heap2(heapMem);

	// 	for (int i = 0; i < 15; i++) {
	// 		int tmp = r(-10000, 10000);
	// 		some = heap.push(tmp);
	// 	}

	// 	heap.merge(heap2);
	// }

	// printf("# %d\n", heap.M[some].val);
	// heap.decrease(some, heap.M[some].val - 1000);

	// for (int i = 0; !heap.empty() && i < 20; i++) {
	// 	printf("%d\n", heap.top());
	// 	heap.pop();
	// }

	PHeap<int> even(heapMem), odd(heapMem);

	for (int i = 0; i < 1000000; i++) {
		even.push(i*2);
		odd.push(i*2+1);
	}

	even.merge(odd);

	while (!odd.empty()) {
		printf("%d ", odd.top());
		odd.pop();
	}
	printf("\n");

	while (!even.empty()) {
		printf("%d ", even.top());
		even.pop();
	}
	printf("\n");
	return 0;
}
