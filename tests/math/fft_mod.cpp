#include "../../lib/math/fft_mod.h"
#include "../testing.h"

namespace kactl {
	typedef vector<ll> vl;
	const ll mod = (119<<23)+1, root = 62;

	ll modpow(ll a, ll e) { // a^e mod m
		ll t = 1 % mod;
		while (e) {
			if (e % 2) t = t*a % mod;
			e /= 2; a = a*a % mod;
		}
		return t;
	}

	void ntt(vl& a, vl& rt, vl& rev, int n) {
		rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int k = 1; k < n; k *= 2)
			for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
					ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
					a[i + j + k] = (z > ai ? ai - z + mod : ai - z);
					ai += (ai + z >= mod ? z - mod : z);
		}
	}

	vl conv(vl& a, vl& b) {
		if (a.empty() || b.empty())
			return {};
		int s = sz(a)+sz(b)-1, B = 32 - __builtin_clz(s), n = 1 << B;
		vl L(a), R(b), out(n), rt(n, 1), rev(n);
		L.resize(n), R.resize(n);
		rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << B) / 2;
		ll curL = mod / 2, inv = modpow(n, mod - 2);
		for (int k = 2; k < n; k *= 2) {
			ll z[] = {1, modpow(root, curL /= 2)};
			rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
		}
		ntt(L, rt, rev, n); ntt(R, rt, rev, n);
		rep(i,0,n) out[-i & (n-1)] = L[i] * R[i] % mod * inv % mod;
		ntt(out, rt, rev, n);
		return {out.begin(), out.begin() + s};
	}
};

vector<ll> naiveConvolve(vector<ll>& A, vector<ll>& B) {
	int len = sz(A) + sz(B) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	A.resize(n); B.resize(n);

	vector<ll> ret(sz(A));
	rep(i, 0, n) rep(j, 0, n) {
		auto& x = ret[(i+j)&(n-1)];
		x = (x + A[i]*B[j]);
	}

	ret.resize(len);
	return ret;
}

void randData(vector<ll>& data) {
	each(d, data) d = r(0, 1000000);
}

void checkWithNaiveConv() {
	for (int i = 0; i < 14; i++) {
		int n = 1 << i;

		vector<ll> d1(n), d2(n);
		randData(d1);
		randData(d2);

		vector<ll> x1 = d1;
		convLong(x1, d2);
		vector<ll> x2 = naiveConvolve(d1, d2);

		ll diff = 0;
		rep(j, 0, n) {
			auto d = abs(x1[i]-x2[i]);
			diff = max(diff, d);
		}

		deb(i, n, diff);
	}
}

using conv_t = function<vector<ll>(vector<ll>& a, vector<ll>& b)>;

void benchConv(const char *name, conv_t conv) {
	auto start = now();

	int n = 1e6;
	vector<ll> a(n), b(n);
	iota(all(a), 15435);
	iota(all(b), 53455);

	rep(i, 0, 5) {
		a = conv(a, b);
		a.resize(n);
		a.swap(b);
	}

	cout << name << " " << since(start) << "ms (" << a[12345] << ")" << endl;
}

int main() {
	cerr << fixed << setprecision(10);

	checkWithNaiveConv();

	benchConv("kactl convolve", kactl::conv);

	benchConv("our convolve", [](vector<ll> a, vector<ll>& b) {
		convolve(a, b);
		return a;
	});

	benchConv("our convolve long", [](vector<ll> a, vector<ll>& b) {
		convLong(a, b);
		return a;
	});

	return 0;
}
