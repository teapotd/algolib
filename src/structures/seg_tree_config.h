#ifdef PLUS // (+; sum, max, max count)
	using T = int;
	static constexpr T ID = 0;

	struct Agg {
		T sum{0}, vMax{INT_MIN}, nMax{0};

		void leaf(T x) {
			sum = vMax = x; nMax = 1;
		}

		void merge(const Agg& r) {
			if (vMax < r.vMax) nMax = r.nMax;
			else if (vMax == r.vMax) nMax += r.nMax;
			vMax = max(vMax, r.vMax);
			sum += r.sum;
		}

		bool apply(T& lazy, T& x, int size) {
			lazy += x;
			sum += x*size;
			vMax += x;
			return 1;
		}
	};
#endif
