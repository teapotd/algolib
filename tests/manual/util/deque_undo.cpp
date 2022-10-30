#include "../../../src/template.h"

struct DataStructure {
	vector<pii> stack;
	int numOperations = 0;

	int time() {
		return sz(stack);
	}

	void rollback(int t) {
		assert(t >= 0 && t <= sz(stack));
		numOperations += sz(stack)-t;
		stack.resize(t);
	}

	void insert(int x, int y) {
		stack.pb({x, y});
		numOperations++;
	}
};

#include "../../../src/util/deque_undo.h"
#include "../testing.h"

constexpr int PUSH_FRONT = 0;
constexpr int PUSH_BACK = 1;
constexpr int POP_FRONT = 2;
constexpr int POP_BACK = 3;

vi randOps(int n, bool deque) {
	int cnt[2] = {};
	vi ret;

	rep(i, 0, n) {
		vi opts = {PUSH_FRONT, PUSH_BACK};

		if (deque) {
			if (cnt[0]+cnt[1] > 0) {
				opts.pb(POP_FRONT);
				opts.pb(POP_BACK);
			}
		} else if (cnt[0] > 0) {
			opts.pb(POP_FRONT);
		} else if (cnt[1] > 0) {
			opts.pb(POP_BACK);
		}

		int k = opts[r(0, sz(opts)-1)];
		ret.pb(k);

		if (k == PUSH_FRONT) cnt[0]++;
		else if (k == PUSH_BACK) cnt[1]++;
		else if (k == POP_FRONT) cnt[0]--;
		else if (k == POP_BACK) cnt[1]--;
	}

	return ret;
}

vi logBoundOps(int n) {
	vi ret(n, PUSH_BACK);
	rep(i, 0, n) {
		ret.pb(PUSH_FRONT);
		ret.pb(POP_BACK);
	}
	return ret;
}

vi alternatePops(int n) {
	vi ret(n, PUSH_BACK);
	ret.resize(n*2, PUSH_FRONT);
	rep(i, 0, n) {
		ret.pb(POP_FRONT);
		ret.pb(POP_BACK);
	}
	return ret;
}

int testTwoStacks(const vi& ops) {
	vector<pii> stacks[2];
	DequeUndo deq;

	rep(i, 0, sz(ops)) {
		int k = ops[i];
		pii e = {i, i+123};

		if (k == PUSH_FRONT) deq.push(e, 0), stacks[0].pb(e);
		else if (k == PUSH_BACK) deq.push(e, 1), stacks[1].pb(e);
		else if (k == POP_FRONT) deq.pop(0), stacks[0].pop_back();
		else if (k == POP_BACK) deq.pop(1), stacks[1].pop_back();

		assert(sz(stacks[0]) + sz(stacks[1]) == sz(deq.ds.stack));
		assert(areElemsUnique(deq.ds.stack));
		assert(isSubseq(deq.ds.stack, stacks[0]));
		assert(isSubseq(deq.ds.stack, stacks[1]));
	}

	return deq.ds.numOperations;
}

int testDeque(const vi& ops) {
	deque<pii> naive;
	DequeUndo deq;

	rep(i, 0, sz(ops)) {
		int k = ops[i];
		pii e = {i, i+123};

		if (k == PUSH_FRONT) deq.push(e, 0), naive.push_front(e);
		else if (k == PUSH_BACK) deq.push(e, 1), naive.push_back(e);
		else if (k == POP_FRONT) deq.pop(0), naive.pop_front();
		else if (k == POP_BACK) deq.pop(1), naive.pop_back();

		vector<pii> tmp1 = deq.ds.stack, tmp2(all(naive));
		sort(all(tmp1));
		sort(all(tmp2));
		assert(tmp1 == tmp2);
	}

	return deq.ds.numOperations;
}

int simulateOnly(const vi& ops) {
	DequeUndo deq;

	rep(i, 0, sz(ops)) {
		int k = ops[i];
		pii e = {i, i+123};

		if (k == PUSH_FRONT) deq.push(e, 0);
		else if (k == PUSH_BACK) deq.push(e, 1);
		else if (k == POP_FRONT) deq.pop(0);
		else if (k == POP_BACK) deq.pop(1);
	}

	return deq.ds.numOperations;
}

int main() {
	deb(testTwoStacks(randOps(1000, false)));
	deb(testDeque(randOps(1000, true)));

	deb(testTwoStacks(logBoundOps(1000)));
	deb(testTwoStacks(alternatePops(1000)));

	deb(simulateOnly(randOps(200000, true)));
	deb(simulateOnly(logBoundOps(200000)));
	deb(simulateOnly(alternatePops(200000)));

	for (int i = 1;; i++) {
		testTwoStacks(randOps(200, false));
		testDeque(randOps(200, true));
		if (i % 5000 == 0) deb(i);
	}
	return 0;
}
