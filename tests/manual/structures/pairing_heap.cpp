#include "../../../src/structures/pairing_heap.h"
#include "../testing.h"

PHeap<int>::Vnode heapMem;

template<class T>
int countChildren(T& que) {
	int n = 0;
	if (que.root < 0) return -1;
	int cur = que.M[que.root].child;

	while (cur >= 0) {
		cur = que.M[cur].next;
		n++;
	}
	return n;
}

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

	PHeap<int> que(heapMem);
	// priority_queue<int, vector<int>, greater<int>> que;

	for (int i = 0; i < 1000000; i++) {
		que.push(rnd());
	}

	while (!que.empty()) {
		// printf("%d ", countChildren(que));
		que.pop();
		// printf("%d\n", countChildren(que));
	}
	return 0;
}
