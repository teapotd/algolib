#include "../template.h"

template<class T, class Cmp = less<T>>
struct PHeap {
	struct Elem;
	using ElemP = unique_ptr<Elem>;

	struct Elem {
		T top;
		vector<ElemP> sub;

		Elem(T x = T()) { top = x; }
	};

	ElemP elem;

	ElemP merge(ElemP l, ElemP r) {
		if (!l) return move(r);
		if (!r) return move(l);
		assert(l != r);

		if (Cmp()(l->top, r->top)) {
			l->sub.push_back(move(r));
			return move(l);
		}

		r->sub.push_back(move(l));
		return move(r);
	}

	bool     empty()          { return !elem; }
	const T& top()            { assert(elem); return elem->top; }
	void     push(const T& x) { elem = merge(move(elem), ElemP(new Elem(x))); }
	void     merge(PHeap&& l) { elem = merge(move(elem), move(l.elem)); }

	void pop() {
		assert(elem);
		auto& sub = elem->sub;

		for (int i = 0; i+1 < sz(sub); i += 2)          sub[i] = merge(move(sub[i]), move(sub[i+1]));
		for (int i = (sz(sub)-1)/2*2-2; i >= 0; i -= 2) sub[i] = merge(move(sub[i]), move(sub[i+2]));

		elem = (elem->sub.empty() ? nullptr : move(elem->sub[0]));
	}
};
