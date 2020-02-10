#if TREE_PLUS // (+; sum, max, max count)
	using T = int;
	const T ID = 0;

	struct Agg {
		T sum{0}, vMax{INT_MIN}, nMax{0};

		void leaf() {
			sum = vMax = 0; nMax = 1;
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
#elif TREE_MAX // (max; max, max count)
	using T = int;
	const T ID = INT_MIN;

	struct Agg {
		T vMax{INT_MIN}, nMax{0};

		void leaf() {
			vMax = 0; nMax = 1;
		}

		void merge(const Agg& r) {
			if (vMax < r.vMax) nMax = r.nMax;
			else if (vMax == r.vMax) nMax += r.nMax;
			vMax = max(vMax, r.vMax);
		}

		bool apply(T& lazy, T& x, int size) {
			if (vMax <= x) nMax = size;
			lazy = max(lazy, x);
			vMax = max(vMax, x);
			return 1;
		}
	};
#elif TREE_SET // (=; sum, max, max count)
	// Set ID to some unused value
	using T = int;
	const T ID = INT_MIN;

	struct Agg {
		T sum{0}, vMax{INT_MIN}, nMax{0};

		void leaf() {
			sum = vMax = 0; nMax = 1;
		}

		void merge(const Agg& r) {
			if (vMax < r.vMax) nMax = r.nMax;
			else if (vMax == r.vMax) nMax += r.nMax;
			vMax = max(vMax, r.vMax);
			sum += r.sum;
		}

		bool apply(T& lazy, T& x, int size) {
			lazy = x;
			sum = x*size;
			vMax = x;
			nMax = size;
			return 1;
		}
	};
#elif TREE_BEATS // (+, min; sum, max)
	// time: amortized O(lg n) if not using +
	//       amortized O(lg^2 n) if using +
	using T = Pii; // +, min
	const T ID = {0, INT_MAX};

	struct Agg {
		int vMax{INT_MIN}, nMax{0}, max2{INT_MIN};
		int sum{0};

		void leaf() {
			sum = vMax = 0; nMax = 1;
		}

		void merge(const Agg& r) {
			if (r.vMax > vMax) {
				max2 = vMax;
				vMax = r.vMax;
				nMax = r.nMax;
			} else if (r.vMax == vMax) {
				nMax += r.nMax;
			} else if (r.vMax > max2) {
				max2 = r.vMax;
			}
			max2 = max(max2, r.max2);
			sum += r.sum;
		}

		bool apply(T& lazy, T& x, int size) {
			if (max2 != INT_MIN && max2+x.x >= x.y)
				return 0;

			lazy.x += x.x;
			sum += x.x*size;
			vMax += x.x;
			if (max2 != INT_MIN) max2 += x.x;

			if (x.y < vMax) {
				sum -= (vMax-x.y) * nMax;
				vMax = x.y;
			}
			lazy.y = vMax;
			return 1;
		}
	};
#endif
