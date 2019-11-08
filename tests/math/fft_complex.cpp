#include "../../src/math/fft_complex.h"
#include "../testing.h"

namespace kactl {
	typedef long double ld;
	typedef complex<double> C;
	typedef vector<double> vd;
	typedef vector<ll> vl;

	void fft(vector<C>& a) {
		int n = sz(a), L = 31 - __builtin_clz(n);
		static vector<complex<long double>> R(2, 1);
		static vector<C> rt(2, 1);  // (^ 10% faster if double)
		for (static int k = 2; k < n; k *= 2) {
			R.resize(n); rt.resize(n);
			auto x = polar(1.0L, ld(M_PI) / k); // M_PI, lower-case L
			rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
		}
		Vi rev(n);
		rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
		rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int k = 1; k < n; k *= 2)
			for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
				// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
				auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
				C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
	}

	vd conv(vd& a, vd& b) {
		if (a.empty() || b.empty()) return {};
		vd res(sz(a) + sz(b) - 1);
		int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
		vector<C> in(n), out(n);
		copy(all(a), begin(in));
		rep(i,0,sz(b)) in[i].imag(b[i]);
		fft(in);
		each(x, in) x *= x;
		rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
		fft(out);
		rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
		return res;
	}

	vl convMod(vl &a, vl &b) {
		if (a.empty() || b.empty()) return {};
		vl res(sz(a) + sz(b) - 1);
		int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(MOD));
		vector<C> L(n), R(n), outs(n), outl(n);
		rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
		rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
		fft(L), fft(R);
		rep(i,0,n) {
			int j = -i & (n - 1);
			outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
			outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / C(0, 1);
		}
		fft(outl), fft(outs);
		rep(i,0,sz(res)) {
			ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
			ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
			res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
			if (res[i] < 0) res[i] += MOD;
		}
		return res;
	}
};

template<class T>
vector<T> naiveConvolve(vector<T> A, vector<T> B) {
	int len = sz(A) + sz(B) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	A.resize(n); B.resize(n);

	vector<T> ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) {
		auto& x = ret[(i+j)&(n-1)];
		x = x + A[i]*B[j];
	}

	ret.resize(len);
	return ret;
}

void randData(vector<ll>& data) {
	each(d, data) d = r(-1000, 1000);
}

void randData(vector<dbl>& data) {
	each(d, data) d = dbl(r(-1000, 1000));
}

void randData(vector<cmpl>& data) {
	each(d, data) d = cmpl(r(-1000, 1000), r(-1000, 1000));
}

void checkRealConvWithNaive() {
	for (int i = 0; i < 14; i++) {
		int n = 1 << i;

		vector<dbl> d1(n), d2(n);
		randData(d1);
		randData(d2);

		vector<dbl> x1 = convolve(d1, d2);
		vector<dbl> x2 = naiveConvolve(d1, d2);

		assert(sz(x1) == sz(x2));

		double diff = 0;
		rep(j, 0, sz(x1)) {
			auto d = abs(x1[i]-x2[i]);
			diff = max(max(diff, real(d)), imag(d));
		}

		deb(i, n, diff);
	}
}

template<class T>
using conv_t = vector<T>(*)(vector<T>& a, vector<T>& b);

template<class T>
void benchConv(const char *name, conv_t<T> conv) {
	auto start = now();

	int n = 1e6;
	vector<T> a(n), b(n);
	iota(all(a), 15435);
	iota(all(b), 53455);

	rep(i, 0, 10) {
		a = conv(a, b);
		a.resize(n);
		a.swap(b);
	}

	cout << name << " " << since(start) << "ms" << endl;
}

int main() {
	cerr << fixed << setprecision(10);

	checkRealConvWithNaive();

	benchConv<dbl>("kactl convolve", kactl::conv);
	benchConv<dbl>("our convolve", convolve);

	benchConv<ll>("kacl convolve mod", kactl::convMod);
	benchConv<ll>("our convolve mod", convMod);

	return 0;
}
